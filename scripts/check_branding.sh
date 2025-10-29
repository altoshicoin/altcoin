#!/usr/bin/env bash
set -euo pipefail

ALLOW='altcoind|altcoin-cli|altcoin-tx|altcoin-wallet|altcoin-qt|altcoin-node|altcoin-gui|altcoin_splash|qt_argv|PACKAGE_URL|PACKAGE_BUGREPORT|PACKAGE_TARNAME|github.com/altoshicoin/altcoin|altcoin.conf|litecoin.conf|bltcb'

TARGETS=(
  'src/rpc/**'
  'src/wallet/rpc*.cpp'
  'src/qt/*.cpp'
  'src/qt/forms/*.ui'
  'src/util/message.cpp'
  'src/init.cpp'
  '!**/test/**'
  '!**/forms.backup/**'
  '!**/*.rc'
  '!**/*.bak*'
)

RG_ARGS=(); for t in "${TARGETS[@]}"; do RG_ARGS+=(-g "$t"); done
RG_ARGS+=( --glob '!test/**' --glob '!src/test/**' --glob '!src/libmw/test/**' --glob '!src/qt/test/**' --glob '!src/qt/forms.backup/**' --glob '!src/Makefile.test.include' --glob '!src/Makefile.qttest.include' )
RG_ARGS+=( --glob '!test/**' --glob '!src/test/**' --glob '!src/libmw/test/**' --glob '!src/qt/test/**' --glob '!src/qt/forms.backup/**' )
tmp=/tmp/branding_leaks.txt; : > "$tmp"

set +e
( rg -n -S '\blitecoin(s)?\b' "${RG_ARGS[@]}" || true ) \
| grep -Evi "$ALLOW" | tee "$tmp" >/dev/null
set -e

if [ -s "$tmp" ]; then
  echo "Branding leak(s) found above"; exit 1
else
  echo "Branding check passed."
fi

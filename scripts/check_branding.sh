#!/usr/bin/env bash
set -euo pipefail

ALLOW='altcoind|litecoin-cli|litecoin-tx|litecoin-wallet|altcoin-qt|litecoin-node|litecoin-gui|litecoin_splash|qt_argv|PACKAGE_URL|PACKAGE_BUGREPORT|PACKAGE_TARNAME|github.com/altoshicoin/altcoin|litecoin\.conf'

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

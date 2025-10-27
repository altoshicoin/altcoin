#!/usr/bin/env bash
set -euo pipefail

# Allow-list: tool names, URLs, config fallback, and known artifacts we keep as-is.
ALLOW='litecoind|litecoin-cli|litecoin-tx|litecoin-wallet|litecoin-qt|litecoin-node|litecoin-gui|litecoin_splash|qt_argv|PACKAGE_URL|PACKAGE_BUGREPORT|PACKAGE_TARNAME|github.com/litecoin-project/litecoin|litecoin\.conf'

# Limit to user-visible/runtime sources only.
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

# Build ripgrep args from TARGETS
RG_ARGS=()
for t in "${TARGETS[@]}"; do RG_ARGS+=(-g "$t"); done

tmp=/tmp/branding_leaks.txt
: > "$tmp"

# Run the search, but don't let "no matches" kill the script.
set +e
( rg -n -S '\blitecoin(s)?\b' "${RG_ARGS[@]}" || true ) \
| grep -Evi "$ALLOW" | tee "$tmp" >/dev/null
set -e

if [ -s "$tmp" ]; then
  echo "Branding leak(s) found above"
  exit 1
else
  echo "Branding check passed."
fi

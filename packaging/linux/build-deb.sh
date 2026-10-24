#!/usr/bin/env bash
# Builds a Release binary, runs the tests, and produces the .deb package.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
cmake --preset linux-release
cmake --build --preset linux-release
ctest --preset linux-release
(cd build/linux-release && cpack -G DEB)
ls -l build/linux-release/*.deb

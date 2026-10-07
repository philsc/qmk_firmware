#!/bin/bash
#
# Builds the ergodox_ez/base:phil firmware inside Docker and flashes it to the keyboard.
#
# Run with sudo so Docker and the USB device are accessible:
#
#   sudo keyboards/ergodox_ez/keymaps/phil/flash.sh
#
# Build artifacts are owned by the invoking user (via SUDO_UID/SUDO_GID) so they don't end up owned
# by root in the checkout.

set -euo pipefail

readonly IMAGE="qmk_cli:phil"
readonly KEYMAP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly REPO_ROOT="$(cd "${KEYMAP_DIR}/../../../.." && pwd)"
readonly HEX="ergodox_ez_base_phil.hex"
readonly CA_BUNDLE="/etc/ssl/certs/ca-certificates.crt"
readonly BUILD_UID="${SUDO_UID:-$(id -u)}"
readonly BUILD_GID="${SUDO_GID:-$(id -g)}"

echo "Building Docker image ${IMAGE}..."
docker build --secret id=ca,src="${CA_BUNDLE}" -t "${IMAGE}" "${KEYMAP_DIR}"

echo "Compiling firmware..."
docker run --rm --user "${BUILD_UID}:${BUILD_GID}" -e HOME=/tmp -w /qmk_firmware \
    -v "${REPO_ROOT}":/qmk_firmware "${IMAGE}" make ergodox_ez/base:phil

echo "Flashing ${HEX}. Press the reset button on the keyboard now."
docker run --rm --privileged -v /dev:/dev -v "${REPO_ROOT}":/qmk_firmware "${IMAGE}" \
    teensy_loader_cli -mmcu=atmega32u4 -w -v "/qmk_firmware/${HEX}"

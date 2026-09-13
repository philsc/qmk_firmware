# Build image for this keymap.
#
# The stock qmk_cli image ships Python 3.14, which removed ast.Num that this
# QMK checkout still uses (lib/python/qmk/math.py). Run qmk from a venv on the
# image's system Python 3.13 instead.
#
#   docker build -t qmk_cli:phil keyboards/ergodox_ez/keymaps/phil
#   docker run --rm --user $(id -u):$(id -g) -e HOME=/tmp -w /qmk_firmware \
#       -v "$PWD":/qmk_firmware qmk_cli:phil make ergodox_ez/base:phil
#   docker run --rm --privileged -v /dev:/dev -v "$PWD":/qmk_firmware qmk_cli:phil \
#       teensy_loader_cli -mmcu=atmega32u4 -w -v /qmk_firmware/ergodox_ez_base_phil.hex
FROM ghcr.io/qmk/qmk_cli
RUN /usr/bin/python3.13 -m venv --without-pip /opt/qmk-venv \
 && /opt/uv/tools/qmk/bin/python3 -m pip download -q -d /tmp/pip pip \
 && WHL=$(ls /tmp/pip/pip-*.whl) && PYTHONPATH=$WHL /opt/qmk-venv/bin/python3 -m pip install -q $WHL \
 && /opt/qmk-venv/bin/pip install -q qmk appdirs argcomplete colorama dotty-dict hid hjson 'jsonschema>=4' 'milc>=1.4.2' pygments pyserial pyusb pillow \
 && rm -rf /tmp/pip
ENV PATH=/opt/qmk-venv/bin:$PATH

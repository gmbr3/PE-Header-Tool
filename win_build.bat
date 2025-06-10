rmdir /s /q build
meson setup build --prefix /
meson compile -C build
meson install -C build --destdir ..

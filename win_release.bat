rmdir /s /q build
meson setup build --buildtype release --prefix /
meson compile -C build
meson install -C build --destdir ../release

windeployqt --release release\bin
del release\bin\vc_redist.x64.exe


# Как запустить

```bash
git clean -fd
autoreconf -fisv
./configure --localedir=<path> --prefix=<same path>
make
make install
```
# gol-tui

Game of Life as a [rawterm](https://github.com/ttibsi/rawterm) terminal UI application

![](https://github.com/user-attachments/assets/a42d161f-19d8-4a62-80e2-d9c3ca53acdf)

### To Use

Run `zig build` to compile and `./zig-out/bin/gol-tui` to run. This has only
been tested with zig `0.13.0`.
Press `q` to quit and `space` to pause the application. Press any key to continue.

Enter your initial board layout as XY coordinates in `config.json` file.

### Dependancies
* nolhmann/JSON for json parsing
* ttibsi/rawterm for TUI management

### To update rawterm
```console
zig fetch --save=rawterm git+https://github.com/ttibsi/rawterm#db991bfe15a22299664af3f44c74c02f746af75f
```

Replace everything after the `#` at the end with the git hash

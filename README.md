# clover-bridge



## 実行方法

`run.sh` を実行するか、次のコマンドを入力してください。

```
$ cmake -B out .
$ cmake --build out
$ ./out/clover-bridge
```

cmakeが導入されていない場合は

```
$ brew install cmake    # Homebrewが導入されたmacOSの場合
```

などの方法で cmake をインストールしてください。



## 実行確認環境

- macOS Monterey 12.0.1
- CMake 3.22.0
- Apple clang version 13.0.0

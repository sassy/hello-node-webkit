hello-node-webkit
=================

NodeWebkitを試しに使ってみただけ。

# 使い方

```
$ npm install
$ npm start
```

# hello モジュールビルド

node-webkitのバージョンが0.11.2であるため、それにあわせてビルドする

```
$ npm install -g nw-gyp
$ cd hello
$ nw-gyp rebuild --target=0.11.2
```


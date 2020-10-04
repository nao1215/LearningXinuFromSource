## XINUをソースコードから学習する
[XINU (Xinu Is Not Unix )](https://ja.wikipedia.org/wiki/Xinu)は、パデュー大学のダグラス・カマーが教育目的で開発したReal Time OSです。<br>
OS勉強用のソースコードとして、XINUを選択した理由は以下の通りです。
 - 小規模（ = C言語が約1万LOCであれば、読み切れる）
 - 産業用途での使用実績がある事（= 実運用に耐えられる設計である事）
 - C言語の文法が古くない事（= 古いUNIXは小規模であるが、文法が古くて読みづらい）
 - 副読書が存在する事（[Xinuオペレーティングシステムデザイン 改訂2版](https://www.kadokawa.co.jp/product/301912000740/)）

## 本リポジトリの使い方
本リポジトリにはソースコードの調査結果として、Doxygenスタイルのコメントをソースコード中に残します。<br>
Doxygenから生成したHTMLファイルは、[docsディレクトリ以下](./docs/html/)もしくは[GitHub Pages](https://nao1215.github.io/LearningXinuFromSource/html/index.html)で確認できます<br>

## XINUオリジナルソースコードの出典
XINUオリジナルソースコードは、[パデュー大学](https://xinu.cs.purdue.edu/)からダウンロードできます。
- [Beagle Board Black版（ARM version、本リポジトリ）](https://xinu.cs.purdue.edu/files/Xinu-code-BeagleBoneBlack.tar.gz)
- [Intel Galileo board版（X86 version）](https://xinu.cs.purdue.edu/files/Xinu-code-Galileo.tar.gz)
- [Virtual Box用の開発環境（vbox 6.1.12による動作確認版)](ftp://ftp.cs.purdue.edu/pub/comer/private/Xinu/xinu-vbox-appliances.tar.gz)

## XINUのビルド方法

```
 $ cd <PROJECT_ROOT>/compile
 $ make
```

## ライセンス
XINUソースコードは、[XINUのライセンス](./COPYRIGHT)に従います。<br>
「docsディレクトリ以下」および「Doxygenスタイルのコメント部分」は、[MIT License](./LICENSE)に従います。
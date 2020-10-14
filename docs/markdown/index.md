# XINU をソースコードから学習する {#mainpage}

## 初めに

[XINU (Xinu Is Not Unix )](https://ja.wikipedia.org/wiki/Xinu)は、パデュー大学のダグラス・カマーが教育目的で開発した Real Time OS です。<br>
OS 勉強用のソースコードとして、XINU を選択した理由は以下の通りです。

- 小規模（ = C 言語が約 1 万 LOC であれば、読み切れる）
- 産業用途での使用実績がある事（= 実運用に耐えられる設計である事）
- C 言語の文法が古くない事（= 古い UNIX は小規模であるが、文法が古くて読みづらい）
- 副読書が存在する事（[Xinu オペレーティングシステムデザイン 改訂 2 版](https://www.kadokawa.co.jp/product/301912000740/)）

## XINU オリジナルソースコードの出典

XINU オリジナルソースコードは、[パデュー大学](https://xinu.cs.purdue.edu/)からダウンロードできます。

- [Beagle Bone Black 版（ARM version、本ドキュメントで使用している Version）](https://xinu.cs.purdue.edu/files/Xinu-code-BeagleBoneBlack.tar.gz)
- [Intel Galileo board 版（X86 version）](https://xinu.cs.purdue.edu/files/Xinu-code-Galileo.tar.gz)
- [Virtual Box 用の開発環境（vbox 6.1.12 による動作確認版)](ftp://ftp.cs.purdue.edu/pub/comer/private/Xinu/xinu-vbox-appliances.tar.gz)

パデュー大学から取得した Beagle Bone Black 向けの XINU コードに対して、日本語コメントを追加したコードは以下の方法で取得できます。

```
$ git clone https://github.com/nao1215/LearningXinuFromSource.git
```

## XINU のビルド方法

```
 $ cd <PROJECT_ROOT>/compile
 $ make
```

## ライセンス

XINU ソースコードは、[XINU のライセンス](./COPYRIGHT)に従います。<br>
「docs ディレクトリ以下」および「Doxygen スタイルのコメント部分」は、[MIT License](./LICENSE)に従います。

## Contact information

Twitter：[ARC_AED](https://twitter.com/ARC_AED)<br>
メール ：n.chika156\@gmail.com

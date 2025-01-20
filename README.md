# Password Analysis

このプロジェクトは、パスワード解析ツールです。指定されたIPアドレス、IDを使用してパスワード解析を行います。

## 使用方法

以下のコマンドを使用して実行します：

```sh
./pascheck <IP Address> <ID> <Password length> <Number of times>
```

例：

```
./pascheck 49.212.180.152 user123 12 10
```

## ビルド方法

このプロジェクトはCMakeを使用してビルドします。以下の手順に従ってください：

Microsoft Visual Studio Community 2022をインストールします。<br />
以下のリンクからダウンロードしてください↓<br />
https://visualstudio.microsoft.com/ja/vs/community/

vcpkgをインストールします。
1. Githubからcloneする。

2. クローンディレクトリの"bootstrap-vcpkg.bat"を実行する。<br />
→ "vcpkg.exe"が生成される。

3. 上記クローンディレクトリにて管理者権限でコマンドプロンプトを開き、以下のコマンドを実行する。

```
.\vcpkg.exe integrate install
```

上記に続いてvcpkgにlibssh2ライブラリをインストールします。<br />
vcpkgのクローンディレクトリにて以下のコマンドを実行する。

```
.\vcpkg.exe install libssh2
```

## ファイル構成

- src: ソースコードディレクトリ
    - main.cpp: メインプログラム
    - analysis.cpp: 解析ロジックの実装
    - analysis.hpp: 解析ロジックのヘッダーファイル
- CMakeLists.txt: CMakeビルド設定ファイル
- CMakeSettings.json: Visual Studio用CMake設定ファイル
- README.md: このファイル

## ライセンス

このプロジェクトはMITライセンスの下で公開されています。詳細はLICENSEファイルを参照してください。

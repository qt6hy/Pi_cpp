// ConsoleApplication1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <ios>     // std::left, std::right
#include <iomanip> // std::setw(int), std::setfill(char)
#include <chrono>
#include <iostream>
#include <cstdio>

int main()
{
    auto start = std::chrono::system_clock::now(); // 計測開始時間

    int base = 10000;     // 基底
    int n = 8400;         // 計算項数
    int i{};                // ループ変数
    int temp{};             // 一時変数/繰り上がり
    int out{};              // 出力値
    int denom{};            // 分母

#ifdef __GNUC__ // gcc
    int numerator[8400]{ [0 ... 8399] = base / 5 };  // 分子
#else
    int numerator[8400]{};  // 分子

    for (i = 0; i < n; i++) {
        numerator[i] = base / 5;
    }
#endif

    for (n = 8400; n > 0; n -= 14) {
        temp = 0;
        for (i = n - 1; i > 0; i--) {
            denom = 2 * i - 1;
            temp = temp * i + numerator[i] * base;
            numerator[i] = temp % denom;
            temp /= denom;
        }
        //std::cout << std::setfill('0') << std::right << std::setw(4) << (out + temp / base); // this is more expensive than std::printf
        std::printf("%04d", out + temp / base);
        out = temp % base;
    }

    auto end = std::chrono::system_clock::now();  // 計測終了時間

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //処理に要した時間をミリ秒に変換
    
    std::cout << elapsed << " ms";

    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
 * 概要:
 * このプログラムはPOSIX Threadsライブラリ(pthread)を使用して、
 * デタッチスレッドを生成する基本的な例を示しています。
 * デタッチスレッドはメインスレッドから切り離され、終了時に自動的に
 * リソースが解放されます。
 * 
 * 処理内容:
 * 1. 複数のデタッチスレッドを生成します
 * 2. 各スレッドは独立して動作し、終了後は自動的にリソースが解放されます
 * 3. メインスレッドはスレッドの終了を待機せずに処理を続行します
 * 
 * 実行結果:
 * メインプログラムがスレッドを順番に生成し、各スレッドが実行を開始します。
 * メインスレッドはスレッドの終了を待たずに処理を続行します。
 * スレッドはバックグラウンドで処理を実行し、終了時に自動的にリソースが解放されます。
 *
 * コンパイル方法:
 * gcc -o pthread_detach pthread_detach.c -pthread
 *
 * 実行方法:
 *% ./pthread_detach 
メインプログラム: デタッチスレッドを作成します
メインプログラム: デタッチスレッド 0 を作成します
メインプログラム: デタッチスレッド 1 を作成します
メインプログラム: デタッチスレッド 2 を作成します
メインプログラム: デタッチスレッド 3 を作成します
メインプログラム: デタッチスレッド 4 を作成します
メインプログラム: 全てのスレッドを作成しました
メインプログラム: デタッチスレッドの終了を待たずに処理を続行します
メインプログラム: 6秒間スリープします
デタッチスレッド 0 が開始されました
デタッチスレッド 0 は 2 秒間スリープします
デタッチスレッド 3 が開始されました
デタッチスレッド 3 は 2 秒間スリープします
デタッチスレッド 4 が開始されました
デタッチスレッド 4 は 3 秒間スリープします
デタッチスレッド 1 が開始されました
デタッチスレッド 1 は 3 秒間スリープします
デタッチスレッド 2 が開始されました
デタッチスレッド 2 は 4 秒間スリープします
デタッチスレッド 0 が終了します
デタッチスレッド 3 が終了します
デタッチスレッド 4 が終了します
デタッチスレッド 1 が終了します
デタッチスレッド 2 が終了します
メインプログラム: 終了します
 */

#define NUM_THREADS 5

// スレッド用の関数
void *detached_thread_function(void *arg) {
    int thread_id = *((int *)arg);
    printf("デタッチスレッド %d が開始されました\n", thread_id);
    
    // スレッドの処理をシミュレート
    // 各スレッドは異なる時間スリープして、非同期動作を示す
    int sleep_time = (thread_id % 3) + 2;
    printf("デタッチスレッド %d は %d 秒間スリープします\n", thread_id, sleep_time);
    sleep(sleep_time);
    
    printf("デタッチスレッド %d が終了します\n", thread_id);
    
    free(arg); // 引数用に割り当てたメモリを解放
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int i, rc;
    
    // スレッド属性の初期化
    pthread_attr_init(&attr);
    
    // スレッドをデタッチ状態に設定
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    printf("メインプログラム: デタッチスレッドを作成します\n");
    
    // スレッドを作成
    for (i = 0; i < NUM_THREADS; i++) {
        printf("メインプログラム: デタッチスレッド %d を作成します\n", i);
        
        // スレッドIDを渡すためのメモリを割り当て
        int *thread_id = (int *)malloc(sizeof(int));
        *thread_id = i;
        
        // デタッチスレッドを生成
        rc = pthread_create(&threads[i], &attr, detached_thread_function, (void *)thread_id);
        
        if (rc) {
            printf("エラー: pthread_create() の戻り値は %d\n", rc);
            exit(-1);
        }
    }
    
    // スレッド属性を破棄
    pthread_attr_destroy(&attr);
    
    printf("メインプログラム: 全てのスレッドを作成しました\n");
    printf("メインプログラム: デタッチスレッドの終了を待たずに処理を続行します\n");
    
    // デタッチスレッドが実行を完了する前にメインスレッドが終了しないように、
    // 少し待機する（実際のアプリケーションでは別の同期メカニズムを使用することが多い）
    printf("メインプログラム: 6秒間スリープします\n");
    sleep(6);
    
    printf("メインプログラム: 終了します\n");
    
    // メインスレッドを終了する
    // pthread_exit(NULL)を使用せずにreturnを使用することで、
    // メインスレッドが終了すると全てのスレッドも強制終了することを示す
    return 0;
} 
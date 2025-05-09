#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * 概要:
 * このプログラムはPOSIX Threadsライブラリ(pthread)を使用して、
 * 複数のスレッドを生成し、それらの終了を待機する基本的な例を示しています。
 * 
 * 処理内容:
 * 1. 10個のスレッドを生成します
 * 2. 各スレッドは単純な処理（カウントアップ）を実行します
 * 3. メインスレッドは全てのスレッドの終了を待機します
 * 4. 各スレッドが終了するとその情報を表示します
 * 
 * 実行結果:
 * メインプログラムがスレッドを順番に生成し、各スレッドが実行を開始します。
 * スレッドは並行して動作するため、実行結果のスレッド終了順序は実行ごとに
 * 異なる可能性があります。全スレッドが終了すると、メインプログラムも終了します。
 *
 * コンパイル方法:
 * gcc -o pthreads pthreads.c -pthread
 * 
 * 実行方法:
 * ./pthreads
 * 
 * 実行結果:
 * スレッドが実行されるタイミングはOSに委ねられているため、順番はバラバラ。
 * % ./pthreads 
メインプログラム: スレッドを作成します
メインプログラム: スレッド 0 を作成します
メインプログラム: スレッド 1 を作成します
メインプログラム: スレッド 2 を作成します
メインプログラム: スレッド 3 を作成します
スレッド 0 が実行中です
メインプログラム: スレッド 4 を作成します
スレッド 3 が実行中です
メインプログラム: スレッド 5 を作成します
スレッド 1 が実行中です
スレッド 5 が実行中です
メインプログラム: スレッド 6 を作成します
...
 */

#define NUM_THREADS 10

// 関数のプロトタイプ宣言
void wait_for_threads(pthread_t *threads, int num_threads);

// スレッド用の関数
void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    printf("スレッド %d が実行中です\n", thread_id);
    
    // スレッドの処理をシミュレート
    for (int i = 0; i < 5; i++) {
        // 何か処理を行う
        printf("スレッド %d が %d 回目のループを実行中です\n", thread_id, i);
    }
    
    printf("スレッド %d が終了します\n", thread_id);
    
    free(arg); // 引数用に割り当てたメモリを解放
    pthread_exit(NULL);
}

// メイン関数
int main() {
    pthread_t threads[NUM_THREADS];
    int i, rc;
    
    printf("メインプログラム: スレッドを作成します\n");
    
    // スレッドを作成
    for (i = 0; i < NUM_THREADS; i++) {
        printf("メインプログラム: スレッド %d を作成します\n", i);
        
        // スレッドIDを渡すためのメモリを割り当て
        int *thread_id = (int *)malloc(sizeof(int));
        *thread_id = i;
        
        // スレッドを生成
        rc = pthread_create(&threads[i], NULL, thread_function, (void *)thread_id);
        //  pthread_join(threads[i], NULL); // 作成直後に待機させると、順序が保証される。が、並行性は失われる
        
        if (rc) {
            printf("エラー: pthread_create() の戻り値は %d\n", rc);
            exit(-1);
        }
    }
    
    // すべてのスレッドの終了を待機
    wait_for_threads(threads, NUM_THREADS);
    
    printf("メインプログラム: 終了します\n");
    pthread_exit(NULL);
}

// すべてのスレッドの終了を待機する関数
void wait_for_threads(pthread_t *threads, int num_threads) {
    void *status;
    
    for (int i = 0; i < num_threads; i++) {
        int rc = pthread_join(threads[i], &status);
        
        if (rc) {
            printf("エラー: pthread_join() の戻り値は %d\n", rc);
            exit(-1);
        }
        
        printf("メインプログラム: スレッド %d が完了しました\n", i);
    }
}

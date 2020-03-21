#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wait.h>

/* fungsi untuk mengecek apakah
 * input berupa angka */
int cekAngka(char argv[]) {
    int length = strlen(argv);
    for (int i=0;i<length; i++)
        if (!isdigit(argv[i]))
        {
            return 0;
        }
    return 1;
}

/* fungsi untuk mengecek apakah
 * input berupa '*' */
int cekBintang(char argv[]) {
    int length = strlen(argv);
    
    if(length==1) {
        if(argv[0]=='*') {
            return 1;
        }
    }
    return 0;
}

/* fungsi untuk mengecek apakah
 * file path valid */
int cekPath(char * path){
    FILE *file;
    if ((file = fopen(path, "r")))
    {
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}

int main(int argc, char *argv[]) {

/* mengecek apakah argumen = 5 */
    if(argc != 5) {
        printf("Input tidak valid \n");
        exit(EXIT_FAILURE);
    }

/* mengecek crontab */
        int check = 0;
        int error = 0;
        int tmp[4];
        int valid[4];

        for(int i=1; i<=3; i++) {
                if(cekAngka(argv[i])==1) {
                    check++;
                    valid[i] = 1;
                }
                else {
                    if(cekBintang(argv[i])==1) {
                        [i] = 1;
                        check++;
                        valid[i] = 1;
                    }
                    else {
                        error++;
                    }
                }
                if(valid[i]!=1) {
                    if(i==1) {
                        printf("Input detik tidak valid \n");
                    }
                    if(i==2) {
                        printf("input menit tidak valid \n");
                    }
                    if(i==3) {
                        printf("input jam tdk valid \n");
                    }
                }
        }
        // printf("%d\n", check);

    /* Mengubah argumen string menjadi integer */
        int detik = atoi(argv[1]);
        int menit = atoi(argv[2]);
        int jam = atoi(argv[3]);
        
        if(check>0) {
            if(detik < 0 || detik >59) {
                printf("input detik tidak valid \n");
                error++;
            }
            if(menit < 0 || menit > 59) {
                printf("input menit tidak valid \n");
                error++;
            }
            if(jam < 0 || jam > 23) {
                printf("input jam tidak valid \n");
                error++;
            }
        }
            int filepath = 0;

            if(cekPath(argv[4])) {
                filepath = 1;
            }
            else {
                printf("file path tidak valid \n");
            }

        /* Jika input tidak valid */
            if(error > 0) {
                exit(EXIT_FAILURE);
            }

        //late daemon

        pid_t pid, sid;        // Variabel untuk menyimpan PID

        pid = fork();     // Menyimpan PID dari Child Process

        /* Keluar saat fork gagal
        * (nilai variabel pid < 0) */
        if (pid < 0) {
            exit(EXIT_FAILURE);
        }

        /* Keluar saat fork berhasil
        * (nilai variabel pid adalah PID dari child process) */
        if (pid > 0) {
            exit(EXIT_SUCCESS);
        }

        umask(0);

        sid = setsid();
        if (sid < 0) {
            exit(EXIT_FAILURE);
        }

        if ((chdir("/")) < 0) {
            exit(EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while (1) {
            time_t waktu;
            struct tm *time_info;

            waktu = time(NULL);
            time_info = localtime(&waktu);

        /* Cek apakah inputan cron berupa angka atau '*' */
            if ((time_info->tm_sec == detik || [1] == 1) && (time_info->tm_min == menit || [2]==1) && 
            (time_info->tm_hour == jam || [3]==1) && filepath==1){
                pid_t child_id;
                child_id = fork();

                int status;

                if (child_id == 0) {    
                    char *arg[] = {"bash", argv[4], NULL};
                    execv("/bin/bash", arg);
                }
                else{
			        while((wait(&status)) > 0);
		        }
            }
           sleep(1);
        }

    }
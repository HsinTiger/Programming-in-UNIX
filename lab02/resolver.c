#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void search_directory(char *path, char *magic_number);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s directory magic-number\n", argv[0]);
    return 1;
  }
  search_directory(argv[1], argv[2]);
  return 0;
}

void search_directory(char *path, char *magic_number) {
  DIR *dir;
  struct dirent *entry;
  struct stat file_info;
  char full_path[512];
  int magic_len = strlen(magic_number);

  dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }
    //(a&&b) != 0
    //   printf("-------entry = %d\n",(entry = readdir(dir)));
  while ((entry = readdir(dir)) != NULL) {
    // printf("entry = %d\n",entry);
    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue;
      }
      snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
      search_directory(full_path, magic_number);
    } else {
      snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
      if (stat(full_path, &file_info) == -1) {
        perror("stat");
        continue;
      }
      if ((file_info.st_mode & S_IFMT) == S_IFREG) {
        FILE *file = fopen(full_path, "r");
        if (file == NULL) {
          perror("fopen");
          continue;
        }
        char buffer[512];
        size_t nread;
        while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        //   if (nread >= magic_len && memcmp(buffer, magic_number, magic_len) == 0) {
        if (nread >= magic_len && strstr(buffer, magic_number) != NULL) {
            printf("%s\n", full_path);
            fclose(file);
            closedir(dir);
            return;
          }
        }
        fclose(file);
      }
    }
    // printf("-------entry = %d\n",entry);
  }

  closedir(dir);
}





// #include <stdio.h>       // 引入標準輸入輸出庫
// #include <stdlib.h>      // 引入標準函式庫
// #include <string.h>      // 引入字串處理庫
// #include <dirent.h>      // 引入目錄庫
// #include <sys/stat.h>    // 引入檔案狀態庫

// void search_directory(char *path, char *magic_number);   // 宣告自定義函式

// int main(int argc, char *argv[]) {   // 主程式
//   if (argc != 3) {   // 檢查傳入參數數量是否為3
//     printf("Usage: %s directory magic-number\n", argv[0]);   // 如果不是3個，印出提示信息
//     return 1;   // 程式異常結束
//   }
//   search_directory(argv[1], argv[2]);   // 執行自定義函式
//   return 0;   // 程式正常結束
// }

// void search_directory(char *path, char *magic_number) {   // 定義自定義函式
//   DIR *dir;   // 宣告目錄指標
//   struct dirent *entry;   // 宣告目錄項目結構體指標
//   struct stat file_info;   // 宣告檔案狀態結構體
//   char full_path[512];   // 宣告完整路徑變數
//   int magic_len = strlen(magic_number);   // 計算魔數字串長度

//   dir = opendir(path);   // 打開目錄
//   if (dir == NULL) {   // 如果打開目錄失敗
//     perror("opendir");   // 印出錯誤信息
//     return;   // 返回
//   }

//   while ((entry = readdir(dir)) != NULL) {   // 遍歷目錄項目
//     if (entry->d_type == DT_DIR) {   // 如果目錄項目是目錄
//       if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {   // 如果目錄項目是"."或".."
//         continue;   // 跳過
//       }
//       snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);   // 構造完整路徑
//       search_directory(full_path, magic_number);   // 遞歸調用自定義函式
//     } else {   // 如果目錄項目是檔案
//       snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);   // 構造完整路徑
//       if (stat(full_path, &file_info) == -1) {   // 取得檔案狀態
//         perror("stat");   // 印出錯誤
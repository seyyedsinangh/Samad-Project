#include "menu.h"
#include "testcase.h"

int main() {
    char adrs[200];
    char file1[200],file2[200],file3[200],file4[200],file5[200],file6[200],file7[200],file8[200];
    int command;
    printf("Enter the address of a folder to create files for information:\n>>");
    fgets(adrs,200,stdin);
    if (adrs[strlen(adrs)-1]=='\n') adrs[strlen(adrs)-1]='\0';
    sprintf(file1,"%s/temp.bin",adrs);
    temp_file_name = &file1[0];
    sprintf(file2,"%s/userinfo.bin",adrs);
    user_info_file_name = &file2[0];
    sprintf(file3,"%s/selfinfo.bin",adrs);
    self_info_file_name = &file3[0];
    sprintf(file4,"%s/foodinfo.bin",adrs);
    food_info_file_name = &file4[0];
    sprintf(file5,"%s/mealplaninfo.bin",adrs);
    meal_plan_info_file_name = &file5[0];
    sprintf(file6,"%s/news.bin",adrs);
    news_file_name = &file6[0];
    sprintf(file7,"%s/polls.bin",adrs);
    polls_file_name = &file7[0];
    sprintf(file8,"%s/reserve.bin",adrs);
    reserve_file_name = &file8[0];
    register_first_admin();
    while (1) {
        printf("1.Work with the menu\n2.Work with the test-case\n");
        scanf("%d",&command);
        fflush(stdin);
        if (command==1) {
            main_menu();
            break;
        } else if (command==2) {
            printf("Enter the address of the input text:\n>>");
            fgets(adrs,200,stdin);
            if (adrs[strlen(adrs)-1]=='\n') adrs[strlen(adrs)-1]='\0';
            ftst_in = fopen(adrs,"rb");
            printf("Enter the address of the output text:\n>>");
            fgets(adrs,200,stdin);
            if (adrs[strlen(adrs)-1]=='\n') adrs[strlen(adrs)-1]='\0';
            ftst_out = fopen(adrs,"wb");
            first_menu_tstc();
            fclose(ftst_in);
            fclose(ftst_out);
            break;
        } else {
            printf("Not defined.Try again.\n");
        }
    }
    return 0;
}




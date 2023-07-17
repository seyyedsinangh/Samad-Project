#ifndef SystemManager_h
#define SystemManager_h

#include "variables.h"



//Function declarations
int define_self(self_info);
int define_food(food_info);
int define_meal_plan(int,date,char *,int,int);
int add_news(news);
int add_poll(poll);


//1 = success , 2 = permission_denied
int define_self (self_info def_self) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *finfo = fopen(self_info_file_name,"ab");
    fwrite(&def_self,sizeof(self_info),1,finfo);
    fclose(finfo);
    return 1;
}

//1 = success , 2 = permission_denied
int define_food (food_info def_food) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *finfo = fopen(food_info_file_name,"ab");
    fwrite(&def_food,sizeof(food_info),1,finfo);
    fclose(finfo);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int define_meal_plan (int inp_self_id,date inp_meal_date,char *inp_meal_food_type,int inp_food_id,int inp_count) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *fself_info = fopen(self_info_file_name,"rb");
    FILE *ffood_info = fopen(food_info_file_name,"rb");
    self_info check_self;
    food_info check_food;
    while (1) {
        fread(&check_self,sizeof(self_info),1,fself_info);
        if (feof(fself_info)) {
            fclose(fself_info);
            return 0;
        }
        if (inp_self_id==check_self.self_id) {
            fclose(fself_info);
            break;
        }
    }
    while (1) {
        fread(&check_food,sizeof(food_info),1,ffood_info);
        if (feof(ffood_info)) {
            fclose(ffood_info);
            return 0;
        }
        if (inp_food_id==check_food.food_id) {
            fclose(ffood_info);
            break;
        }
    }
    meal_plan def_meal_plan;
    FILE *fmeal_plan_info = fopen(meal_plan_info_file_name,"ab");
    def_meal_plan.self_id = inp_self_id;
    strcpy(def_meal_plan.gender_type,check_self.type);
    strcpy(def_meal_plan.meal_type,inp_meal_food_type);
    if (strcmp(inp_meal_food_type,"lunch")==0) {
        def_meal_plan.meal_time_limit = check_self.lunch_time_limit;
    } else {
        def_meal_plan.meal_time_limit = check_self.dinner_time_limit;
    }
    strcpy(def_meal_plan.self_name,check_self.name);
    strcpy(def_meal_plan.self_location,check_self.location);
    strcpy(def_meal_plan.food_name,check_food.name);
    def_meal_plan.meal_day = inp_meal_date;
    def_meal_plan.food_id = inp_food_id;
    def_meal_plan.price = check_food.price;
    def_meal_plan.count = inp_count;
    fwrite(&def_meal_plan,sizeof(meal_plan),1,fmeal_plan_info);
    fclose(fmeal_plan_info);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int charge_student_account (long int charge_amount,char *username) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    user_info check_user;
    while (1) {
        fread(&check_user,sizeof(user_info),1,finfo);
        if (feof(finfo)) {
            fclose(finfo);
            return 0;
        }
        if (strcmp(username,check_user.user_id)==0) {
            check_user.charge += charge_amount;
            fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
            fwrite(&check_user,sizeof(user_info),1,finfo);
            break;
        }
    }
    fclose(finfo);
    return 1;
}

//1 = success , 2 = permission_denied
int add_news (news text) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *fnews = fopen(news_file_name,"ab");
    fwrite(&text,sizeof(news),1,fnews);
    fclose(fnews);
    return 1;
}

//1 = success , 2 = permission_denied
int add_poll (poll inp_poll) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *fpolls = fopen(polls_file_name,"ab");
    fwrite(&inp_poll,sizeof(poll),1,fpolls);
    fclose(fpolls);
    return 1;
}



#endif //SystemManager_h

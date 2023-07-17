#ifndef StudentPart_h
#define StudentPart_h

#include "variables.h"



//Function declarations
int charge_account(long int);
int send_charge(long int,char *,char *);
int reserve_food(int,int,char *,date);
int take_food(int,date,char *);
int cancel_reserve(date,char *);
int check_news(void);
int voting(void);




//1 = success , 2 = permission_denied
int charge_account (long int charge_amount) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    logined_user.charge += charge_amount;
    user_info check_user;
    while (fread(&check_user,sizeof(user_info),1,finfo)>=1) {
        if (strcmp(logined_user.user_id,check_user.user_id)==0) {
            fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
            fwrite(&logined_user,sizeof(user_info),1,finfo);
            break;
        }
    }
    fclose(finfo);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int send_charge (long int charge_amount,char *username,char *name) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    if (logined_user.charge < charge_amount) return 2;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    user_info check_user;
    while (1) {
        fread(&check_user,sizeof(user_info),1,finfo);
        if (feof(finfo)) {
            fclose(finfo);
            return 0;
        } else if (strcmp(username,check_user.user_id)==0 && strcasecmp(name,check_user.name)==0) {
            fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
            check_user.charge += charge_amount;
            fwrite(&check_user,sizeof(user_info),1,finfo);
            break;
        }
    }
    rewind(finfo);
    while (1) {
        fread(&check_user,sizeof(user_info),1,finfo);
        if (strcmp(logined_user.user_id,check_user.user_id)==0) {
            fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
            logined_user.charge -= charge_amount;
            fwrite(&logined_user,sizeof(user_info),1,finfo);
            break;
        }
    }
    fclose(finfo);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int reserve_food(int inp_self_id,int inp_food_id,char *inp_meal_type,date reserve_date) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    meal_plan check_plan;
    FILE *fmeal_plan = fopen(meal_plan_info_file_name,"r+b");
    while (1) {
        fread(&check_plan,sizeof(meal_plan),1,fmeal_plan);
        if (feof(fmeal_plan)) {
            fclose(fmeal_plan);
            return 0;
        } else if (date_comp(check_plan.meal_day,reserve_date)==0 && meal_gender_type_check(check_plan.gender_type,logined_user.gender) && check_plan.self_id==inp_self_id && check_plan.food_id==inp_food_id && strcmp(check_plan.meal_type,inp_meal_type)==0) {
            if (logined_user.charge>=check_plan.price && check_plan.count>0 && comparing_date_for_reserve(now_timedate.date_moment,check_plan.meal_day)) break;
            else {
                fclose(fmeal_plan);
                return 2;
            }
        }
    }
    fseek(fmeal_plan,(-1)*sizeof(meal_plan),SEEK_CUR);
    check_plan.count--;
    fwrite(&check_plan,sizeof(meal_plan),1,fmeal_plan);
    fclose(fmeal_plan);
    FILE *fuser_info = fopen(user_info_file_name,"r+b");
    logined_user.charge -= check_plan.price;
    user_info check_user;
    while (fread(&check_user,sizeof(user_info),1,fuser_info)>=1) {
        if (strcmp(logined_user.user_id,check_user.user_id)==0) {
            fseek(fuser_info,(-1)*sizeof(user_info),SEEK_CUR);
            fwrite(&logined_user,sizeof(user_info),1,fuser_info);
            break;
        }
    }
    fclose(fuser_info);
    FILE *freserve = fopen(reserve_file_name,"r+b");
    if (freserve==NULL) freserve = fopen(reserve_file_name,"wb");
    reserve_info check_reserve;
    while (fread(&check_reserve,sizeof(reserve_info),1,freserve)>=1) {
        if (strcmp(logined_user.user_id,check_reserve.user_id)==0 && check_reserve.self_id==inp_self_id && check_reserve.food_id==inp_food_id && strcmp(check_reserve.meal_type,inp_meal_type) && date_comp(check_reserve.start_meal.date_moment,reserve_date)==0) {
            fclose(freserve);
            return 2;
        }
    }
    reserve_info res_user;
    res_user.self_id = check_plan.self_id;
    res_user.food_id = check_plan.food_id;
    res_user.price = check_plan.price;
    res_user.start_meal.date_moment = check_plan.meal_day;
    res_user.start_meal.time_moment = check_plan.meal_time_limit.start;
    res_user.finish_time = check_plan.meal_time_limit.end;
    strcpy(res_user.user_id,logined_user.user_id);
    strcpy(res_user.meal_type,check_plan.meal_type);
    fwrite(&res_user,sizeof(reserve_info),1,freserve);
    fclose(freserve);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int take_food (int inp_self_id,date inp_date,char *inp_meal_type) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    FILE *fself_info = fopen(self_info_file_name,"rb");
    self_info check_self;
    while (1) {
        fread(&check_self,sizeof(self_info),1,fself_info);
        if (feof(fself_info)) {
            fclose(fself_info);
            return 0;
        } else if (check_self.self_id==inp_self_id) {
            break;
        }
    }
    fclose(fself_info);
    FILE *freserve = fopen(reserve_file_name,"rb");
    FILE *ftemp = fopen(temp_file_name,"wb");
    reserve_info check_reserve;
    int result = 2;
    while (1) {
        fread(&check_reserve,sizeof(reserve_info),1,freserve);
        if (feof(freserve)) {
            break;
        } else if (strcmp(check_reserve.user_id,logined_user.user_id)==0 && check_reserve.self_id==inp_self_id && date_comp(inp_date,check_reserve.start_meal.date_moment)==0 && strcmp(check_reserve.meal_type,inp_meal_type)==0) {
            if (check_time_for_taking(now_timedate,check_reserve.start_meal,check_reserve.finish_time)) {
                result = 1;
            }
            continue;
        }
        fwrite(&check_reserve,sizeof(reserve_info),1,ftemp);
    }
    fclose(freserve);
    fclose(ftemp);
    freserve = fopen(reserve_file_name,"wb");
    ftemp = fopen(temp_file_name,"rb");
    while (1) {
        fread(&check_reserve,sizeof(reserve_info),1,ftemp);
        if (feof(ftemp)) break;
        fwrite(&check_reserve,sizeof(reserve_info),1,freserve);
    }
    fclose(freserve);
    fclose(ftemp);
    return result;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int cancel_reserve (date inp_date,char *inp_meal_type) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    FILE *freserve = fopen(reserve_file_name,"rb");
    FILE *ftemp = fopen(temp_file_name,"wb");
    reserve_info check_reserve,sav_res;
    int result = 0;
    while (1) {
        fread(&check_reserve,sizeof(reserve_info),1,freserve);
        if (feof(freserve)) {
            break;
        } else if (strcmp(check_reserve.user_id,logined_user.user_id)==0 && date_comp(inp_date,check_reserve.start_meal.date_moment)==0 && strcmp(check_reserve.meal_type,inp_meal_type)==0) {
            if (comparing_time_for_cancel(now_timedate,check_reserve.start_meal)) {
                sav_res = check_reserve;
                result = 1;
                continue;
            } else {
                result = 2;
            }
        }
        fwrite(&check_reserve,sizeof(reserve_info),1,ftemp);
    }
    fclose(freserve);
    fclose(ftemp);
    freserve = fopen(reserve_file_name,"wb");
    ftemp = fopen(temp_file_name,"rb");
    while (1) {
        fread(&check_reserve,sizeof(reserve_info),1,ftemp);
        if (feof(ftemp)) break;
        fwrite(&check_reserve,sizeof(reserve_info),1,freserve);
    }
    fclose(freserve);
    fclose(ftemp);
    if (result!=1) return result;
    meal_plan check_plan;
    FILE *fmeal_plan = fopen(meal_plan_info_file_name,"r+b");
    while (fread(&check_plan,sizeof(meal_plan),1,fmeal_plan)>=1) {
        if (sav_res.self_id==check_plan.self_id && sav_res.food_id==check_plan.food_id && strcmp(sav_res.meal_type,check_plan.meal_type)==0 && date_comp(sav_res.start_meal.date_moment,check_plan.meal_day)==0) {
            check_plan.count++;
            fseek(fmeal_plan,(-1)*sizeof(meal_plan),SEEK_CUR);
            fwrite(&check_plan,sizeof(meal_plan),1,fmeal_plan);
            break;
        }
    }
    fclose(fmeal_plan);
    user_info check_user;
    FILE *fuser_info = fopen(user_info_file_name,"r+b");
    while (fread(&check_user,sizeof(user_info),1,fuser_info)>=1) {
        if (strcmp(logined_user.user_id,check_user.user_id)==0) {
            logined_user.charge += (9*check_plan.price)/10;
            fseek(fuser_info,(-1)*sizeof(user_info),SEEK_CUR);
            fwrite(&logined_user,sizeof(user_info),1,fuser_info);
        }
    }
    fclose(fuser_info);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int check_news (void) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    FILE *fnews = fopen(news_file_name,"rb");
    news temp_news;
    if (fnews==NULL) return 0;
    while (fread(&temp_news,sizeof(news),1,fnews)>=1) {
        if (date_comp(now_timedate.date_moment,temp_news.end_date)<1) {
            fclose(fnews);
            return 1;
        }
    }
    fclose(fnews);
    return 0;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int voting (void) {
    if (strcmp(logined_user.type,"admin")==0) return 2;
    FILE *fpolls = fopen(polls_file_name,"rb");
    poll temp_poll;
    if (fpolls==NULL) return 0;
    while (fread(&temp_poll,sizeof(poll),1,fpolls)>=1) {
        if (date_comp(now_timedate.date_moment,temp_poll.end_date)<1) {
            fclose(fpolls);
            return 1;
        }
    }
    fclose(fpolls);
    return 0;
}



#endif //StudentPart_h

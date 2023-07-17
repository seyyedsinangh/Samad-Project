#ifndef testcase_h
#define testcase_h

#include "UserManagement.h"
#include "SystemManager.h"
#include "StudentPart.h"

//Function declarations
int command_identify(char *);
void first_menu_tstc(void);
int login_tstc(char *);
void register_tstc(int,char *);
void main_menu_tstc(void);
int logout_tstc(char *);
void change_pass_tstc(char *);
void approve_tstc(char *);
void deactivation_tstc(char *);
void remove_tstc(char *);
void change_student_pass_tstc(char *);
void define_self_tstc(char *);
void define_food_tstc(char *);
void charge_account_tstc(char *);
void define_meal_plan_tstc(char *);
void charge_student_account_tstc(char *);
void add_news_tstc(char *);
void add_poll_tstc(char *);
void send_charge_tstc(char *);
void change_datetime_tstc(char *);
void reserve_food_tstc(char *);
void take_food_tstc(char *);
void cancel_reserve_tstc(char *);
void check_news_tstc(char *);
void voting_tstc(char *);


int command_identify (char *command) {
    if (strcmp(command,"login")==0) return 1;
    else if (strcmp(command,"register")==0) return 2;
    else if (strcmp(command,"logout")==0) return 3;
    else if (strcmp(command,"change-pass")==0) return 4;
    else if (strcmp(command,"approve")==0) return 5;
    else if (strcmp(command,"change-student-pass")==0) return 6;
    else if (strcmp(command,"remove-student")==0) return 7;
    else if (strcmp(command,"deactivate")==0) return 8;
    else if (strcmp(command,"define-self")==0) return 9;
    else if (strcmp(command,"define-food")==0) return 10;
    else if (strcmp(command,"define-meal-plan")==0) return 11;
    else if (strcmp(command,"charge-student-account")==0) return 12;
    else if (strcmp(command,"add-news")==0) return 13;
    else if (strcmp(command,"add-poll")==0) return 14;
    else if (strcmp(command,"reserve")==0) return 15;
    else if (strcmp(command,"take-food")==0) return 16;
    else if (strcmp(command,"charge-account")==0) return 17;
    else if (strcmp(command,"send-charge")==0) return 18;
    else if (strcmp(command,"cancel-reserve")==0) return 19;
    else if (strcmp(command,"check-news")==0) return 20;
    else if (strcmp(command,"vote")==0) return 21;
    else if (strcmp(command,"change-datetime")==0) return 22;
    else return 0;
}


void first_menu_tstc (void) {
    char command[MAX2];
    char command_id[MAX3];
    char whole_com[BIGMAX];
    int command_number;
    while (1) {
        fgets(whole_com,BIGMAX,ftst_in);
        if (feof(ftst_in)) break;
        else if (whole_com[0]=='\n') break;
        strcpy(command_id,strtok(whole_com,"#"));
        strcpy(command,strtok(NULL,"#"));
        if (command[strlen(command)-1]=='\n') command[strlen(command)-1]='\0';
        if (command[strlen(command)-1]=='\r') command[strlen(command)-1]='\0';
        command_number = command_identify(command);
        if (command_number==1) {
            if (login_tstc(command_id)!=0) {
                main_menu_tstc();
            }
        } else if (command_number==2) {
            register_tstc(0,command_id);
        } else if (command_number==22) {
            change_datetime_tstc(command_id);
        } else {
            fprintf(ftst_out,"%s#not-found\n",command_id);
        }
    }
}

int login_tstc (char *command_id) {
    char username[MAX2],pass[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(pass,strtok(NULL,"\n"));
    if (pass[strlen(pass)-1]=='\r') pass[strlen(pass)-1]='\0';
    int result = loging_in(username,pass);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else {
        fprintf(ftst_out,"%s#success\n",command_id);
    }
    return result;
}

void register_tstc (int appr,char *command_id) {
    user_info reg;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(reg.name,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(reg.family,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(reg.user_id,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(reg.password,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(reg.national_id,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d%*c%d%*c%d",&reg.birthdate.year,&reg.birthdate.month,&reg.birthdate.day);
    strtok(NULL,":");
    strcpy(reg.gender,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(reg.type,strtok(NULL,"\n"));
    if (reg.type[strlen(reg.type)-1]=='\r') reg.type[strlen(reg.type)-1]='\0';
    reg.approved = appr;
    reg.charge = 0;
    int result = registeration(reg);
    if (result==2) {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    } else {
        fprintf(ftst_out,"%s#success\n",command_id);
    }
}

void change_datetime_tstc (char *command_id) {
    int inp_y,inp_m,inp_d,inp_hour,inp_min;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d-%d-%d",&inp_y,&inp_m,&inp_d);
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%2d%2d",&inp_hour,&inp_min);
    change_datetime(inp_hour,inp_min,inp_y,inp_m,inp_d);
    fprintf(ftst_out,"%s#success\n",command_id);
}

void main_menu_tstc (void) {
    char command[MAX2];
    char command_id[MAX3];
    char whole_com[BIGMAX];
    int command_number;
    while (1) {
        fgets(whole_com,BIGMAX,ftst_in);
        if (feof(ftst_in)) break;
        else if (whole_com[0]=='\n') break;
        strcpy(command_id,strtok(whole_com,"#"));
        strcpy(command,strtok(NULL,"#"));
        if (command[strlen(command)-1]=='\n') command[strlen(command)-1]='\0';
        if (command[strlen(command)-1]=='\r') command[strlen(command)-1]='\0';
        command_number = command_identify(command);
        if (command_number==2) {
            register_tstc(1,command_id);
        } else if (command_number==3) {
            if (logout_tstc(command_id)==1) break;
        } else if (command_number==4) {
            change_pass_tstc(command_id);
        } else if (command_number==5) {
            approve_tstc(command_id);
        } else if (command_number==6) {
            change_student_pass_tstc(command_id);
        } else if (command_number==7) {
            remove_tstc(command_id);
        } else if (command_number==8) {
            deactivation_tstc(command_id);
        } else if (command_number==9) {
            define_self_tstc(command_id);
        } else if (command_number==10) {
            define_food_tstc(command_id);
        } else if (command_number==11) {
            define_meal_plan_tstc(command_id);
        } else if (command_number==12) {
            charge_student_account_tstc(command_id);
        } else if (command_number==13) {
            add_news_tstc(command_id);
        } else if (command_number==14) {
            add_poll_tstc(command_id);
        } else if (command_number==15) {
            reserve_food_tstc(command_id);
        } else if (command_number==16) {
            take_food_tstc(command_id);
        } else if (command_number==17) {
            charge_account_tstc(command_id);
        } else if (command_number==18) {
            send_charge_tstc(command_id);
        } else if (command_number==19) {
            cancel_reserve_tstc(command_id);
        } else if (command_number==20) {
            check_news_tstc(command_id);
        } else if (command_number==21) {
            voting_tstc(command_id);
        } else if (command_number==22) {
            change_datetime_tstc(command_id);
        } else {
            fprintf(ftst_out,"%s#not-found\n",command_id);
        }
    }
}

int logout_tstc (char *command_id) {
    char username[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"\n"));
    if (username[strlen(username)-1]=='\r') username[strlen(username)-1]='\0';
    int result = loging_out(username);
    if (result==2) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else {
        fprintf(ftst_out,"%s#success\n",command_id);
    }
    return result;
}


void change_pass_tstc (char *command_id) {
    char username[MAX2],old_pass[MAX2],new_pass[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(old_pass,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(new_pass,strtok(NULL,"\n"));
    if (new_pass[strlen(new_pass)-1]=='\r') new_pass[strlen(new_pass)-1]='\0';
    int result = change_pass(old_pass,new_pass,username);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void approve_tstc (char *command_id) {
    struct appr_node *appr_list = NULL;
    char temp[MAX2];
    char *check;
    while (1) {
        strtok(NULL,":");
        check = strtok(NULL,"|");
        if (strchr(check,'\n')!=NULL) {
            check[strlen(check)-1]='\0';
            if (check[strlen(check)-1]=='\r') check[strlen(check)-1]='\0';
            strcpy(temp,check);
            add_appr_list(&appr_list,temp);
            break;
        }
        strcpy(temp,check);
        add_appr_list(&appr_list,temp);
    }
    int result = approve(appr_list);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void change_student_pass_tstc (char *command_id) {
    char username[MAX2],new_pass[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(new_pass,strtok(NULL,"\n"));
    if (new_pass[strlen(new_pass)-1]=='\r') new_pass[strlen(new_pass)-1]='\0';
    int result = change_student_pass(username,new_pass);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void remove_tstc (char *command_id) {
    char username[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"\n"));
    if (username[strlen(username)-1]=='\r') username[strlen(username)-1]='\0';
    int result = removal(username);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void deactivation_tstc (char *command_id) {
    char username[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"\n"));
    if (username[strlen(username)-1]=='\r') username[strlen(username)-1]='\0';
    int result = deactivation(username);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void define_self_tstc (char *command_id) {
    self_info info_inp;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&info_inp.self_id);
    strtok(NULL,":");
    strcpy(info_inp.name,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(info_inp.location,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&info_inp.capacity);
    strtok(NULL,":");
    strcpy(info_inp.type,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(info_inp.meal_type,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%2d%2d%*c%2d%2d",&info_inp.lunch_time_limit.start.hour,&info_inp.lunch_time_limit.start.min,&info_inp.lunch_time_limit.end.hour,&info_inp.lunch_time_limit.end.min);
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%2d%2d%*c%2d%2d",&info_inp.dinner_time_limit.start.hour,&info_inp.dinner_time_limit.start.min,&info_inp.dinner_time_limit.end.hour,&info_inp.dinner_time_limit.end.min);
    int result = define_self(info_inp);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void define_food_tstc(char *command_id) {
    food_info info_inp;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&info_inp.food_id);
    strtok(NULL,":");
    strcpy(info_inp.name,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(info_inp.type,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%ld",&info_inp.price);
    int result = define_food(info_inp);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void define_meal_plan_tstc (char *command_id) {
    int inp_self_id,inp_food_id,inp_count;
    date inp_meal_date;
    char inp_meal_food_type[MAX3];
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&inp_self_id);
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d%*c%d%*c%d",&inp_meal_date.year,&inp_meal_date.month,&inp_meal_date.day);
    strtok(NULL,":");
    strcpy(inp_meal_food_type,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&inp_food_id);
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%d",&inp_count);
    int result = define_meal_plan(inp_self_id,inp_meal_date,inp_meal_food_type,inp_food_id,inp_count);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void charge_student_account_tstc (char *command_id) {
    long int charge_amount;
    char username[MAX2];
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(username,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%ld",&charge_amount);
    int result = charge_student_account(charge_amount,username);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void add_news_tstc (char *command_id) {
    news inp_text;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(inp_text.title,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(inp_text.content,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%d%*c%d%*c%d",&inp_text.end_date.year,&inp_text.end_date.month,&inp_text.end_date.day);
    int result = add_news(inp_text);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void add_poll_tstc (char *command_id) {
    poll inp_poll;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(inp_poll.question,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(inp_poll.option1,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(inp_poll.option2,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(inp_poll.option3,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(inp_poll.option4,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%d%*c%d%*c%d",&inp_poll.end_date.year,&inp_poll.end_date.month,&inp_poll.end_date.day);
    int result = add_poll(inp_poll);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void reserve_food_tstc (char *command_id) {
    int inp_food_id;
    int inp_self_id;
    char inp_meal_type[MAX3];
    date reserve_date;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&inp_self_id);
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d%*c%d%*c%d",&reserve_date.year,&reserve_date.month,&reserve_date.day);
    strtok(NULL,":");
    strcpy(inp_meal_type,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"\n"));
    if (temp[strlen(temp)-1]=='\r') temp[strlen(temp)-1]='\0';
    sscanf(temp,"%d",&inp_food_id);
    int result = reserve_food(inp_self_id,inp_food_id,inp_meal_type,reserve_date);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void take_food_tstc (char *command_id) {
    int inp_self_id;
    date inp_date;
    char inp_meal_type[MAX3];
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d",&inp_self_id);
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d%*c%d%*c%d",&inp_date.year,&inp_date.month,&inp_date.day);
    strtok(NULL,":");
    strcpy(inp_meal_type,strtok(NULL,"\n"));
    if (inp_meal_type[strlen(inp_meal_type)-1]=='\r') inp_meal_type[strlen(inp_meal_type)-1]='\0';
    int result = take_food(inp_self_id,inp_date,inp_meal_type);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void charge_account_tstc (char *command_id) {
    long int charge_amount;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%ld",&charge_amount);
    int result = charge_account(charge_amount);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void send_charge_tstc (char *command_id) {
    char user_id[MAX2],user_name[MAX1];
    long int charge_amount;
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(user_id,strtok(NULL,"|"));
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%ld",&charge_amount);
    strtok(NULL,":");
    strcpy(user_name,strtok(NULL,"\n"));
    if (user_name[strlen(user_name)-1]=='\r') user_name[strlen(user_name)-1]='\0';
    int result = send_charge(charge_amount,user_id,user_name);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void cancel_reserve_tstc (char *command_id) {
    date inp_date;
    char inp_meal_type[MAX3];
    char temp[MAX2];
    strtok(NULL,":");
    strcpy(temp,strtok(NULL,"|"));
    sscanf(temp,"%d%*c%d%*c%d",&inp_date.year,&inp_date.month,&inp_date.day);
    strtok(NULL,":");
    strcpy(inp_meal_type,strtok(NULL,"\n"));
    if (inp_meal_type[strlen(inp_meal_type)-1]=='\r') inp_meal_type[strlen(inp_meal_type)-1]='\0';
    int result = cancel_reserve(inp_date,inp_meal_type);
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void check_news_tstc (char *command_id) {
    int result = check_news();
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

void voting_tstc (char *command_id) {
    int result = voting();
    if (result==0) {
        fprintf(ftst_out,"%s#not-found\n",command_id);
    } else if (result==1) {
        fprintf(ftst_out,"%s#success\n",command_id);
    } else {
        fprintf(ftst_out,"%s#permission-denied\n",command_id);
    }
}

#endif //testcase_h

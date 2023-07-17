#ifndef menu_h
#define menu_h

#include "UserManagement.h"
#include "SystemManager.h"
#include "StudentPart.h"


//Function declarations
void main_menu(void);
int login_menu(void);
void register_menu(int);
void student_menu(void);
void admin_menu(void);
void change_pass_menu(void);
void approve_menu(void);
void deactivation_menu(void);
void remove_menu(void);
void change_student_pass_menu(void);
void define_self_menu(void);
void define_food_menu(void);
void charge_account_menu(void);
void define_meal_plan_menu(void);
void charge_student_account_menu(void);
void add_news_menu(void);
void add_poll_menu(void);
void send_charge_menu(void);
void change_datetime_menu(void);
void reserve_food_menu(void);
void take_food_menu(void);
void cancel_reserve_menu(void);
void check_news_menu(void);
void voting_menu(void);
void reserved_foods_list(void);



void main_menu (void) {
    int command;
    while (1) {
        for (int i=0; i<30; i++) printf("*");
        printf("\n<<MAIN MENU>>\n");
        printf("1.Login\n2.Register\n3.Exit\nEnter the number of the command:\n>>");
        fflush(stdin);
        scanf("%d",&command);
        if(command==1) {
            int login_option = login_menu();
            if(login_option==1) {
                admin_menu();
            } else if (login_option==2) {
                student_menu();
            }
        } else if (command==2) {
            register_menu(0);
        } else if (command==3) {
            break;
        } else {
            printf("Not defined,try again!\n");
        }
    }
}

int login_menu (void) {
    int temp;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<LOGIN SECTION>>\n");
    char username[MAX2],pass[MAX2];
    fflush(stdin);
    printf("Enter the username:\n>>");
    scanf("%s",username);
    fflush(stdin);
    printf("Enter the password:\n>>");
    scanf("%s",pass);
    temp = loging_in(username,pass);
    if (temp==0) {
        printf("The user was not found.\n");
    }
    return temp;
}

void register_menu (int appr) {
    user_info info_inp;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<REGISTER SECTION>>\n");
    fflush(stdin);
    printf("Enter the name:\n>>");
    scanf("%s",info_inp.name);
    fflush(stdin);
    printf("Enter the family name:\n>>");
    scanf("%s",info_inp.family);
    fflush(stdin);
    printf("Enter the user id:\n>>");
    scanf("%s",info_inp.user_id);
    fflush(stdin);
    printf("Enter the password:\n>>");
    scanf("%s",info_inp.password);
    fflush(stdin);
    printf("Enter the national id:\n>>");
    scanf("%s",info_inp.national_id);
    fflush(stdin);
    printf("Enter the birthdate(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&info_inp.birthdate.year,&info_inp.birthdate.month,&info_inp.birthdate.day);
    fflush(stdin);
    printf("Enter the gender(male or female):\n>>");
    scanf("%s",info_inp.gender);
    fflush(stdin);
    printf("Enter the type of user(admin or student):\n>>");
    scanf("%s",info_inp.type);
    info_inp.approved = appr;
    info_inp.charge = 0;
    if (registeration(info_inp)==1) {
        printf("The user has successfully been registered.");
        if (appr==0) printf("Wait for the admin's approval.");
        printf("\n");
    }
    else {
        printf("The user has already been registered.\n");
    }
}

void student_menu (void) {
    int command;
    while (1) {
        for (int i=0; i<30; i++) printf("*");
        printf("\n<<STUDENT SECTION>>\n");
        printf("1.Logout\n2.Change password\n3.Charge account\n4.Send charge to a student\n5.Change date and time\n6.Reserve food\n7.Take food\n8.Cancel reserve\n9.Check news\n10.Vote\n11.See the reserved foods\nEnter the number of the command:\n>>");
        fflush(stdin);
        scanf("%d",&command);
        if(command==1) {
            if (loging_out(logined_user.user_id)==1) break;
        } else if (command==2) {
            change_pass_menu();
        } else if (command==3) {
            charge_account_menu();
        } else if (command==4) {
            send_charge_menu();
        } else if (command==5) {
            change_datetime_menu();
        } else if (command==6) {
            reserve_food_menu();
        } else if (command==7) {
            take_food_menu();
        } else if (command==8) {
            cancel_reserve_menu();
        } else if (command==9) {
            check_news_menu();
        } else if (command==10) {
            voting_menu();
        } else if (command==11) {
            reserved_foods_list();
        } else {
            printf("Not defined,try again!\n");
        }
    }
}

void admin_menu (void) {
    int command;
    while (1) {
        for (int i=0; i<30; i++) printf("*");
        printf("\n<<ADMIN SECTION>>\n");
        printf("1.Logout\n2.Change password\n3.Approve users\n4.Deactivate a student\n5.Register a user\n6.Remove a student\n7.Change the password of a student\n8.Define a self\n9.Define a food\n10.Define a meal plan\n11.Charge the account of a student\n12.Add news\n13.Add a poll\n14.Change date and time\nEnter the number of the command:\n>>");
        fflush(stdin);
        scanf("%d",&command);
        if(command==1) {
            if (loging_out(logined_user.user_id)==1) break;
        } else if (command==2) {
            change_pass_menu();
        } else if (command==3) {
            approve_menu();
        } else if (command==4) {
            deactivation_menu();
        } else if (command==5) {
            register_menu(1);
        } else if (command==6) {
            remove_menu();
        } else if (command==7) {
            change_student_pass_menu();
        } else if (command==8) {
            define_self_menu();
        } else if (command==9) {
            define_food_menu();
        } else if (command==10) {
            define_meal_plan_menu();
        } else if (command==11) {
            charge_student_account_menu();
        } else if (command==12) {
            add_news_menu();
        } else if (command==13) {
            add_poll_menu();
        } else if (command==14) {
            change_datetime_menu();
        } else {
            printf("Not defined,try again!\n");
        }
    }
}

void change_pass_menu (void) {
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<CHANGE_PASSWORD SECTION>>\n");
    char old_pass[MAX2],new_pass[MAX2];
    fflush(stdin);
    printf("Enter the old password:\n>>");
    scanf("%s",old_pass);
    fflush(stdin);
    printf("Enter the new password:\n>>");
    scanf("%s",new_pass);
    if (change_pass(old_pass,new_pass,logined_user.user_id)==2) {
        printf("Your old password is not correct.Operation unsuccessful!\n");
    } else {
        printf("Operation successful!\n");
    }
}

void approve_menu (void) {
    int j=1;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    user_info check_user;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<APPROVAL SECTION>>\n");
    printf("Students waiting for approval:\n");
    while (fread(&check_user,sizeof(user_info),1,finfo)>=1) {
        if (check_user.approved==0) {
            printf("%d.%s\n",j++,check_user.user_id);
        }
    }
    fclose(finfo);
    fflush(stdin);
    printf("Enter the user-ids of the students you want to approve (user-id1,user-id2,...):\n>>");
    int indx = 0;
    char c;
    char temp[MAX2];
    int num;
    struct appr_node *appr_list = NULL;
    while (1) {
        indx = 0;
        while (1) {
            c = getchar();
            if (c==',' || c=='\n') {
                temp[indx] = '\0';
                break;
            }
            temp[indx++] = c;
        }
        add_appr_list(&appr_list,temp);
        if (c=='\n') break;
    }
    num = approve(appr_list);
    if (num==0) {
        printf("One or more users couldn't be approved because of not registeration.\n");
    } else {
        printf("Operation successful.\n");
    }
}

void deactivation_menu (void) {
    char username[MAX2];
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<DEACTIVATION SECTION>>\n");
    fflush(stdin);
    printf("Enter the user-id of the student you want to deactivate:\n>>");
    scanf("%s",username);
    if (deactivation(username)==0) {
        printf("The user was not found.Operation unsuccessful!\n");
    } else {
        printf("Operation successful.\n");
    }
}

void remove_menu (void) {
    char username[MAX2];
    int temp;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<REMOVAL SECTION>>\n");
    fflush(stdin);
    printf("Enter the user-id of the student you want to remove:\n>>");
    scanf("%s",username);
    fflush(stdin);
    printf("Enter 1 to confirm or 2 to cancel the operation:\n>>");
    scanf("%d",&temp);
    if (temp==2) {
        printf("The user was not removed.\n");
        return;
    } else if (temp!=1) {
        printf("Not defined.\n");
        return;
    }
    if (removal(username)==0) {
        printf("The user was not found.Operation unsuccessful!\n");
    } else {
        printf("Operation successful.\n");
    }
}

void change_student_pass_menu (void) {
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<CHANGE_STUDENT_PASSWORD SECTION>>\n");
    char username[MAX2],new_pass[MAX2];
    fflush(stdin);
    printf("Enter the username:\n>>");
    scanf("%s",username);
    fflush(stdin);
    printf("Enter the new password:\n>>");
    scanf("%s",new_pass);
    if (change_student_pass(username,new_pass)==0) {
        printf("The user was not found.Operation unsuccessful!\n");
    } else {
        printf("Operation successful!\n");
    }
}

void define_self_menu (void) {
    self_info info_inp;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<DEFINE_SELF SECTION>>\n");
    fflush(stdin);
    printf("Enter the id of the self:\n>>");
    scanf("%d",&info_inp.self_id);
    fflush(stdin);
    printf("Enter the name of the self:\n>>");
    scanf("%s",info_inp.name);
    fflush(stdin);
    printf("Enter the location of the self:\n>>");
    scanf("%s",info_inp.location);
    fflush(stdin);
    printf("Enter the capacity of the self:\n>>");
    scanf("%d",&info_inp.capacity);
    fflush(stdin);
    printf("Enter the type of the self(boyish or girlish):\n>>");
    scanf("%s",info_inp.type);
    fflush(stdin);
    printf("Enter the meal type of the self(lunch, dinner or both):\n>>");
    scanf("%s",info_inp.meal_type);
    fflush(stdin);
    if (strcmp(info_inp.meal_type,"dinner")==0) {
        printf("Enter the dinner limit time(srt_hour:str_min-end_hour:end_min):\n>>");
        scanf("%d:%d-%d:%d",&info_inp.dinner_time_limit.start.hour,&info_inp.dinner_time_limit.start.min,&info_inp.dinner_time_limit.end.hour,&info_inp.dinner_time_limit.end.min);
        info_inp.lunch_time_limit.start.hour = 0;
        info_inp.lunch_time_limit.start.min = 0;
        info_inp.lunch_time_limit.end.hour = 0;
        info_inp.lunch_time_limit.end.min = 0;
    } else if (strcmp(info_inp.meal_type,"lunch")==0) {
        printf("Enter the lunch limit time(srt_hour:str_min-end_hour:end_min):\n>>");
        scanf("%d:%d-%d:%d",&info_inp.lunch_time_limit.start.hour,&info_inp.lunch_time_limit.start.min,&info_inp.lunch_time_limit.end.hour,&info_inp.lunch_time_limit.end.min);
        info_inp.dinner_time_limit.start.hour = 0;
        info_inp.dinner_time_limit.start.min = 0;
        info_inp.dinner_time_limit.end.hour = 0;
        info_inp.dinner_time_limit.end.min = 0;
    } else {
        printf("Enter the lunch limit time(srt_hour:str_min-end_hour:end_min):\n>>");
        scanf("%d:%d-%d:%d",&info_inp.lunch_time_limit.start.hour,&info_inp.lunch_time_limit.start.min,&info_inp.lunch_time_limit.end.hour,&info_inp.lunch_time_limit.end.min);
        fflush(stdin);
        printf("Enter the dinner limit time(srt_hour:str_min-end_hour:end_min):\n>>");
        scanf("%d:%d-%d:%d",&info_inp.dinner_time_limit.start.hour,&info_inp.dinner_time_limit.start.min,&info_inp.dinner_time_limit.end.hour,&info_inp.dinner_time_limit.end.min);
    }
    if (define_self(info_inp)==1) {
        printf("Operation successful.\n");
    }
}

void define_food_menu (void) {
    food_info info_inp;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<DEFINE_FOOD SECTION>>\n");
    fflush(stdin);
    printf("Enter the id of the food:\n>>");
    scanf("%d",&info_inp.food_id);
    fflush(stdin);
    printf("Enter the name of the food:\n>>");
    scanf("%s",info_inp.name);
    fflush(stdin);
    printf("Enter the type of the food(dessert or food):\n>>");
    scanf("%s",info_inp.type);
    fflush(stdin);
    printf("Enter the price of the food:\n>>");
    scanf("%ld",&info_inp.price);
    if (define_food(info_inp)==1) {
        printf("Operation successful.\n");
    }
}

void charge_account_menu (void) {
    long int charge_amount;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<CHARGE_ACCOUNT SECTION>>\n");
    fflush(stdin);
    printf("Enter the amount of charge:\n>>");
    scanf("%ld",&charge_amount);
    fflush(stdin);
    printf("Enter the card number:\n>>");
    scanf("%*s");
    fflush(stdin);
    printf("Enter the pass code:\n>>");
    scanf("%*s");
    if (charge_account(charge_amount)==1) {
        printf("Operation successful.\n");
    }
}

void define_meal_plan_menu (void) {
    int inp_self_id,inp_food_id,inp_count;
    date inp_meal_date;
    char inp_meal_food_type[MAX3];
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<DEFINE_MEAL_PLAN SECTION>>\n");
    fflush(stdin);
    printf("Enter the id of the self:\n>>");
    scanf("%d",&inp_self_id);
    fflush(stdin);
    printf("Enter the date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&inp_meal_date.year,&inp_meal_date.month,&inp_meal_date.day);
    fflush(stdin);
    printf("Enter the meal type(lunch or dinner):\n>>");
    scanf("%s",inp_meal_food_type);
    fflush(stdin);
    printf("Enter the food id:\n>>");
    scanf("%d",&inp_food_id);
    fflush(stdin);
    printf("Enter the count of the food:\n>>");
    scanf("%d",&inp_count);
    if (define_meal_plan(inp_self_id,inp_meal_date,inp_meal_food_type,inp_food_id,inp_count)==0) {
        printf("The self or the food was not defined.Operation unseccessful.\n");
    } else {
        printf("Operation successful.\n");
    }
}

void charge_student_account_menu (void) {
    char username[MAX2];
    long int charge_amount;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<CHARGE_STUDENT_ACCOUNT SECTION>>\n");
    fflush(stdin);
    printf("Enter the user id of the student:\n>>");
    scanf("%s",username);
    fflush(stdin);
    printf("Enter the amount of charge:\n>>");
    scanf("%ld",&charge_amount);
    if (charge_student_account(charge_amount,username)==0) {
        printf("The user was not found.Operation unsuccessful.\n");
    } else {
        printf("Operation successful.\n");
    }
}

void add_news_menu (void) {
    news inp_text;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<ADD_NEWS SECTION>>\n");
    fflush(stdin);
    printf("Enter the title of the news:\n>>");
    fgets(inp_text.title,TITLE,stdin);
    fflush(stdin);
    printf("Enter the content of the news:\n>>");
    fgets(inp_text.content,CONTENT,stdin);
    fflush(stdin);
    printf("Enter the end date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&inp_text.end_date.year,&inp_text.end_date.month,&inp_text.end_date.day);
    if (add_news(inp_text)==1) {
        printf("Operation successful.\n");
    }
}

void add_poll_menu (void) {
    poll inp_poll;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<ADD_POLL SECTION>>\n");
    fflush(stdin);
    printf("Enter the question of the poll:\n>>");
    fgets(inp_poll.question,TITLE,stdin);
    fflush(stdin);
    printf("Enter the option1:\n>>");
    fgets(inp_poll.option1,MAX3,stdin);
    fflush(stdin);
    printf("Enter the option2:\n>>");
    fgets(inp_poll.option2,MAX3,stdin);
    fflush(stdin);
    printf("Enter the option3:\n>>");
    fgets(inp_poll.option3,MAX3,stdin);
    fflush(stdin);
    printf("Enter the option4:\n>>");
    fgets(inp_poll.option4,MAX3,stdin);
    fflush(stdin);
    printf("Enter the end date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&inp_poll.end_date.year,&inp_poll.end_date.month,&inp_poll.end_date.day);
    if (add_poll(inp_poll)==1) {
        printf("Operation successful.\n");
    }
}

void send_charge_menu (void) {
    char username[MAX2];
    long int charge_amount;
    int temp;
    FILE *finfo = fopen(user_info_file_name,"rb");
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<SEND_CHARGE SECTION>>\n");
    fflush(stdin);
    printf("Enter the user id of the student:\n>>");
    scanf("%s",username);
    fflush(stdin);
    printf("Enter the amount of charge:\n>>");
    scanf("%ld",&charge_amount);
    user_info check_user;
    while (1) {
        fread(&check_user,sizeof(user_info),1,finfo);
        if (strcmp(username,check_user.user_id)==0) break;
        else if (feof(finfo)) {
            printf("The user was not found.\n");
            fclose(finfo);
            return;
        }
    }
    fclose(finfo);
    printf("The information of the student:\n\tuser_id:%s\n\tfirst name:%s\n\tfamily name:%s\n",check_user.user_id,check_user.name,check_user.family);
    fflush(stdin);
    printf("Enter 1 to confirm or 2 to cancel the operation:\n>>");
    scanf("%d",&temp);
    if (temp==2) {
        printf("Operation was not completed.\n");
        return;
    }
    else if (temp!=1) {
        printf("Not defined.\n");
        return;
    }
    if (send_charge(charge_amount,check_user.user_id,check_user.name)==2) {
        printf("You don't have enough charge.\n");
    } else {
        printf("Operation successful.\n");
    }
}

void change_datetime_menu (void) {
    int inp_y,inp_m,inp_d,inp_hour,inp_min;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<CHANGE_DATETIME SECTION>>\n");
    fflush(stdin);
    printf("Enter the date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&inp_y,&inp_m,&inp_d);
    fflush(stdin);
    printf("Enter the time(hour:min):\n>>");
    scanf("%d%*c%d",&inp_hour,&inp_min);
    change_datetime(inp_hour,inp_min,inp_y,inp_m,inp_d);
    printf("Operation successful.\n");
}

void reserve_food_menu (void) {
    int i=1;
    int inp_food_id;
    int inp_self_id;
    char inp_meal_type[MAX3];
    date reserve_date;
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<RESERVE SECTION>>\n");
    fflush(stdin);
    printf("Enter the date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&reserve_date.year,&reserve_date.month,&reserve_date.day);
    if (comparing_date_for_reserve(now_timedate.date_moment,reserve_date)) {
        printf("Meals you can reserve for this date:\n");
    } else {
        printf("You can't reserve for this date.\n");
        return;
    }
    meal_plan check_plan;
    FILE *fmeal_plan = fopen(meal_plan_info_file_name,"rb");
    while (fread(&check_plan,sizeof(meal_plan),1,fmeal_plan)>=1) {
        if (date_comp(check_plan.meal_day,reserve_date)==0 && meal_gender_type_check(check_plan.gender_type,logined_user.gender)) {
            printf("%d.\nself id:%d\nself name:%s\nself location:%s\nmeal type:%s\nfood id:%d\nfood name:%s\nprice:%ld\n",i,check_plan.self_id,check_plan.self_name,check_plan.self_location,check_plan.meal_type,check_plan.food_id,check_plan.food_name,check_plan.price);
            i++;
        }
    }
    rewind(fmeal_plan);
    fflush(stdin);
    printf("Enter the self id of the meal you want to reserve:\n>>");
    scanf("%d",&inp_self_id);
    fflush(stdin);
    printf("Enter the food id of the meal you want to reserve:\n>>");
    scanf("%d",&inp_food_id);
    fflush(stdin);
    printf("Enter the meal type of the meal you want to reserve(lunch or dinner):\n>>");
    scanf("%s",inp_meal_type);
    while (1) {
        fread(&check_plan,sizeof(meal_plan),1,fmeal_plan);
        if (date_comp(check_plan.meal_day,reserve_date)==0 && meal_gender_type_check(check_plan.gender_type,logined_user.gender) && check_plan.self_id==inp_self_id && check_plan.food_id==inp_food_id && strcmp(check_plan.meal_type,inp_meal_type)==0) {
            while (logined_user.charge<check_plan.price) {
                printf("You don't have enough charge.Charge your account.\n");
                charge_account_menu();
                for (int i=0; i<30; i++) printf("*");
                printf("\n");
            }
            break;
        } else if (feof(fmeal_plan)) {
            printf("The meal plan was not found.\n");
            fclose(fmeal_plan);
            return;
        }
    }
    fclose(fmeal_plan);
    if (reserve_food(inp_self_id,inp_food_id,inp_meal_type,reserve_date)==1) {
        printf("Operation successful.\n");
    } else {
        printf("The food is finished,you can't reserve this meal.\n");
    }
}

void take_food_menu (void) {
    int inp_self_id;
    date inp_date;
    char inp_meal_type[MAX3];
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<TAKE_FOOD SECTION>>\n");
    fflush(stdin);
    printf("Enter the self id:\n>>");
    scanf("%d",&inp_self_id);
    fflush(stdin);
    printf("Enter the date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&inp_date.year,&inp_date.month,&inp_date.day);
    fflush(stdin);
    printf("Enter the meal type(lunch or dinner):\n>>");
    scanf("%s",inp_meal_type);
    int temp = take_food(inp_self_id,inp_date,inp_meal_type);
    if (temp==1) {
        printf("Operation successful.\n");
    } else if (temp==0) {
        printf("The self was not found.\n");
    } else {
        printf("Operation unsuccessful.\n");
    }
}

void cancel_reserve_menu (void) {
    date inp_date;
    char inp_meal_type[MAX3];
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<TAKE_FOOD SECTION>>\n");
    fflush(stdin);
    printf("Enter the date(year-month-day):\n>>");
    scanf("%d%*c%d%*c%d",&inp_date.year,&inp_date.month,&inp_date.day);
    fflush(stdin);
    printf("Enter the meal type(lunch or dinner):\n>>");
    scanf("%s",inp_meal_type);
    int temp = cancel_reserve(inp_date,inp_meal_type);
    if (temp==1) {
        printf("Operation successful.\n");
    } else if (temp==0) {
        printf("The reserve was not found.\n");
    } else {
        printf("You can't cancel at this moment.\n");
    }
}

void check_news_menu (void) {
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<CHECK_NEWS SECTION>>\n");
    if(check_news()==0) {
        printf("There is no news.\n");
        return;
    }
    FILE *fnews = fopen(news_file_name,"rb");
    news temp_news;
    int i=1;
    while (fread(&temp_news,sizeof(news),1,fnews)>=1) {
        if (date_comp(now_timedate.date_moment,temp_news.end_date)<1) {
            printf("%d.\nTitle:%sContent:%s\n",i,temp_news.title,temp_news.content);
            i++;
        }
    }
    fclose(fnews);
}

void voting_menu (void) {
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<VOTING SECTION>>\n");
    if(voting()==0) {
        printf("There is no poll.\n");
        return;
    }
    FILE *fpolls = fopen(polls_file_name,"rb");
    poll temp_poll;
    int i=1;
    while (fread(&temp_poll,sizeof(poll),1,fpolls)>=1) {
        if (date_comp(now_timedate.date_moment,temp_poll.end_date)<1) {
            printf("%d.\nQuestion:%sOption1:%sOption2:%sOption3:%sOption4:%s\n",i,temp_poll.question,temp_poll.option1,temp_poll.option2,temp_poll.option3,temp_poll.option4);
            i++;
            fflush(stdin);
            printf("Enter your option(1,2,3 or 4):\n>>");
            scanf("%*d");
        }
    }
    fclose(fpolls);
}

void reserved_foods_list (void) {
    for (int i=0; i<30; i++) printf("*");
    printf("\n<<RESERVED_FOODS SECTION>>\n");
    FILE *freserve = fopen(reserve_file_name,"rb");
    FILE *fmeal_plan = fopen(meal_plan_info_file_name,"rb");
    if (freserve==NULL || fmeal_plan==NULL) {
        printf("There is no reserve.\n");
        return;
    }
    reserve_info check_reserve;
    meal_plan check_meal;
    int i=1;
    while (fread(&check_reserve,sizeof(reserve_info),1,freserve)>=1) {
        rewind(fmeal_plan);
        if (strcmp(check_reserve.user_id,logined_user.user_id)==0) {
            while (fread(&check_meal,sizeof(meal_plan),1,fmeal_plan)>=1) {
                if (check_meal.self_id==check_reserve.self_id && check_meal.food_id==check_reserve.food_id && (date_comp(check_meal.meal_day,now_timedate.date_moment)>-1)) {
                    printf("%d.\n",i++);
                    printf("self id:%d\nself name:%s\nself location:%s\nfood id:%d\nfood name:%s\nmeal type:%s\nmeal date:%d-%d-%d\nmeal time:%d:%d-%d:%d\n",check_meal.self_id,check_meal.self_name,check_meal.self_location,check_meal.food_id,check_meal.food_name,check_meal.meal_type,check_meal.meal_day.year,check_meal.meal_day.month,check_meal.meal_day.day,check_meal.meal_time_limit.start.hour,check_meal.meal_time_limit.start.min,check_meal.meal_time_limit.end.hour,check_meal.meal_time_limit.end.min);
                    break;
                }
            }
        }
    }
    if (i==1) {
        printf("There is no reserve.\n");
    }
}

#endif //menu.h

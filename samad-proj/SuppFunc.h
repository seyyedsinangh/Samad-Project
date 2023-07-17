#ifndef SuppFunc_h
#define SuppFunc_h

#include "variables.h"

//Function declarations
void add_appr_list(struct appr_node **,char *);
struct appr_node * CreatingApprNode(char *);
void change_datetime(int,int,int,int,int);
bool comparing_date_for_reserve(date,date);
int date_comp(date,date);
bool meal_gender_type_check(char *,char *);
bool comparing_time_for_cancel(moment,moment);
bool check_time_for_taking(moment,moment,time_hm);
int time_comp(time_hm,time_hm);




struct appr_node * CreatingApprNode (char *user_id) {
    struct appr_node *pnode;
    pnode = (struct appr_node *) malloc(sizeof(struct appr_node));
    strcpy(pnode->user_id,user_id);
    pnode->next = NULL;
    return pnode;
}

void add_appr_list (struct appr_node **head,char *user_id) {
    if (*head==NULL) {
        *head = CreatingApprNode(user_id);
        return;
    }
    struct appr_node *temp = *head;
    while (temp->next!=NULL) temp = temp->next;
    temp->next = CreatingApprNode(user_id);
}

void change_datetime (int hour,int min,int year,int month,int day) {
    now_timedate.date_moment.year = year;
    now_timedate.date_moment.month = month;
    now_timedate.date_moment.day = day;
    now_timedate.time_moment.hour = hour;
    now_timedate.time_moment.min = min;
}

bool comparing_date_for_reserve (date now_date,date reserve_date) {
    if (now_date.year==reserve_date.year && now_date.month==reserve_date.month && reserve_date.day-now_date.day<=14 && reserve_date.day-now_date.day>=2) {
        return true;
    } else if (now_date.year==reserve_date.year && reserve_date.month-now_date.month==1 && reserve_date.day-now_date.day+30<=14 && reserve_date.day-now_date.day+30>=2) {
        return true;
    } else if (reserve_date.year-now_date.year==1 && reserve_date.month==1 && now_date.month==12 && reserve_date.day-now_date.day+30<=14 && reserve_date.day-now_date.day+30>=2) {
        return true;
    } else {
        return false;
    }
}

// 1 = a>b , -1 = a<b , 0 = a=b
int date_comp (date a,date b) {
    if (a.year<b.year) return -1;
    else if (a.year>b.year) return 1;
    else if (a.month<b.month) return -1;
    else if (a.month>b.month) return 1;
    else if (a.day<b.day) return -1;
    else if (a.day>b.day) return 1;
    else return 0;
}

// 1 = a>b , -1 = a<b , 0 = a=b
int time_comp (time_hm a,time_hm b) {
    if (a.hour<b.hour) return -1;
    else if (a.hour>b.hour) return 1;
    else if (a.min<b.min) return -1;
    else if (a.min>b.min) return 1;
    else return 0;
}


bool meal_gender_type_check (char *meal_gender_type,char *user_gender) {
    if (strcmp(meal_gender_type,"boyish")==0 && strcmp(user_gender,"male")==0) return true;
    else if (strcmp(meal_gender_type,"girlish")==0 && strcmp(user_gender,"female")==0) return true;
    else return false;
}


bool comparing_time_for_cancel (moment now_time,moment start_meal) {
    int temp = date_comp(now_time.date_moment,start_meal.date_moment);
    if (temp==-1) return true;
    else if (temp==0) {
        if (start_meal.time_moment.hour - now_time.time_moment.hour > 1) return true;
        else if ((start_meal.time_moment.hour-now_time.time_moment.hour==1) && (start_meal.time_moment.min-now_time.time_moment.min>=0)) return true;
    }
    return false;
}

bool check_time_for_taking (moment now_time,moment start_meal,time_hm finish_meal) {
    int temp1 = date_comp(now_time.date_moment,start_meal.date_moment);
    if (temp1==1) return false;
    else if (temp1==0) {
        int temp2 = time_comp(now_time.time_moment,start_meal.time_moment);
        int temp3 = time_comp(now_time.time_moment,finish_meal);
        if (temp2==0 || (temp2==1 && temp3==-1) || temp3==0) return true;
    }
    return false;
}

#endif //SuppFunc_h

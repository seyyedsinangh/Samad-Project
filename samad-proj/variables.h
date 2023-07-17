#ifndef variables_h
#define variables_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#define BIGMAX 1000
#define MAX1 35
#define MAX2 25
#define MAX3 15
#define TITLE 100
#define CONTENT 500


typedef struct {
    int year;
    int month;
    int day;
} date;

typedef struct {
    char name[MAX1];
    char family[MAX1];
    char user_id[MAX2];
    char national_id[MAX2];
    char password[MAX2];
    char gender[MAX3];
    char type[MAX3]; //admin , student
    date birthdate;
    int approved; //1 = approved , 2 = not approved
    long int charge;
} user_info;

struct appr_node {
    char user_id[MAX2];
    struct appr_node *next;
};

typedef struct {
    int hour;
    int min;
} time_hm;



typedef struct {
    time_hm start;
    time_hm end;
} limit_time;

typedef struct {
    int self_id;
    char name[MAX1];
    char location[MAX1];
    int capacity;
    char type[MAX3];
    char meal_type[MAX3];
    limit_time lunch_time_limit;
    limit_time dinner_time_limit;
} self_info;

typedef struct {
    int food_id;
    char name[MAX1];
    char type[MAX3];
    long int price;
} food_info;


typedef struct {
    int self_id;
    char self_name[MAX1];
    char self_location[MAX1];
    char gender_type[MAX3];
    char meal_type[MAX3];
    limit_time meal_time_limit;
    date meal_day;
    int food_id;
    char food_name[MAX1];
    long int price;
    int count;
} meal_plan;

typedef struct {
    char title[TITLE];
    char content[CONTENT];
    date end_date;
} news;

typedef struct {
    char question[TITLE];
    char option1[MAX3];
    char option2[MAX3];
    char option3[MAX3];
    char option4[MAX3];
    date end_date;
} poll;

typedef struct {
    time_hm time_moment;
    date date_moment;
} moment;


typedef struct {
    int self_id;
    int food_id;
    char meal_type[MAX3];
    moment start_meal;
    time_hm finish_time;
    char user_id[MAX2];
    long int price;
} reserve_info;


moment now_timedate;
user_info logined_user;

char *temp_file_name;
char *user_info_file_name;
char *self_info_file_name;
char *food_info_file_name;
char *meal_plan_info_file_name;
char *news_file_name;
char *polls_file_name;
char *reserve_file_name;

FILE *ftst_in;
FILE *ftst_out;


#endif //variables_h

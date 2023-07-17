#ifndef UserManagement_h
#define UserManagement_h

#include "variables.h"
#include "SuppFunc.h"



//Function declarations
void register_first_admin(void);
int change_pass(char *,char *,char *);
int loging_in(char *,char *);
int registeration(user_info);
int loging_out(char *);
int approve(struct appr_node *);
int deactivation(char *);
int removal(char *);
int change_student_pass(char *,char *);


void register_first_admin (void) {
    user_info first_admin;
    strcpy(first_admin.type,"admin");
    strcpy(first_admin.user_id,"admin");
    strcpy(first_admin.password,"admin");
    first_admin.approved = 1;
    registeration(first_admin);
}

//0 = not_found , 1 = success-admin , 2 = success-student
int loging_in (char *user_id_check,char *pass_check) {
    FILE *finfo = fopen(user_info_file_name,"rb");
    user_info check_user;
    int temp1,temp2,result;
    while (fread(&check_user,sizeof(user_info),1,finfo)>=1) {
        temp1 = strcmp(user_id_check,check_user.user_id);
        temp2 = strcmp(pass_check,check_user.password);
        if (temp1==0 && temp2==0) {
            if (check_user.approved==0) return 0;
            if (strcmp(check_user.type,"admin")==0) result=1;
            else result=2;
            logined_user = check_user;
            fclose(finfo);
            return result;
        }
    }
    fclose(finfo);
    return 0;
}

//1 = success , 2 = permission_denied
int registeration (user_info reg) {
    FILE *finfo = fopen(user_info_file_name,"r+b");
    if (finfo==NULL) finfo = fopen(user_info_file_name,"w+b");
    user_info check_user;
    while (fread(&check_user,sizeof(user_info),1,finfo)>=1) {
        if (strcmp(reg.user_id,check_user.user_id)==0) {
            fclose(finfo);
            return 2;
        }
    }
    fwrite(&reg,sizeof(reg),1,finfo);
    fclose(finfo);
    return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int change_pass (char *old_password,char *new_password,char *username) {
    if (strcmp(username,logined_user.user_id)!=0) return 0;
    if (strcmp(old_password,logined_user.password)!=0) return 2;
    strcpy(logined_user.password,new_password);
    user_info check_user;
    FILE *finfo = fopen(user_info_file_name,"r+b");
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

//1 = success , 2 = not_found
int loging_out (char *user_id_check) {
    if (strcmp(user_id_check,logined_user.user_id)!=0) return 2;
    else return 1;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int approve (struct appr_node *appr_list) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    user_info check_user;
    struct appr_node *temp;
    int result = 1;
    while (appr_list!=NULL) {
        rewind(finfo);
        while (1) {
            fread(&check_user,sizeof(user_info),1,finfo);
            if (feof(finfo)) {
                result = 0;
                break;
            } else if (strcmp(appr_list->user_id,check_user.user_id)==0) {
                check_user.approved = 1;
                fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
                fwrite(&check_user,sizeof(user_info),1,finfo);
                break;
            }
        }
        temp = appr_list;
        appr_list = appr_list->next;
        free(temp);
    }
    fclose(finfo);
    return result;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int deactivation (char *username) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    user_info check_user;
    int result = 1;
    while (1) {
        fread(&check_user,sizeof(user_info),1,finfo);
        if (feof(finfo)) {
            result = 0;
            break;
        } else if (strcmp(username,check_user.user_id)==0) {
            check_user.approved = 0;
            fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
            fwrite(&check_user,sizeof(user_info),1,finfo);
            break;
        }
    }
    fclose(finfo);
    return result;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int removal (char *username) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    FILE *finfo = fopen(user_info_file_name,"rb");
    FILE *ftemp = fopen(temp_file_name,"wb");
    user_info check_user;
    int result = 0;
    while (1) {
        fread(&check_user,sizeof(user_info),1,finfo);
        if (feof(finfo)) {
            break;
        } else if (strcmp(username,check_user.user_id)==0) {
            result = 1;
            continue;
        }
        fwrite(&check_user,sizeof(user_info),1,ftemp);
    }
    fclose(finfo);
    fclose(ftemp);
    finfo = fopen(user_info_file_name,"wb");
    ftemp = fopen(temp_file_name,"rb");
    while (1) {
        fread(&check_user,sizeof(user_info),1,ftemp);
        if (feof(ftemp)) break;
        fwrite(&check_user,sizeof(user_info),1,finfo);
    }
    fclose(finfo);
    fclose(ftemp);
    return result;
}

// 0 = not_found , 1 = success , 2 = permission_denied
int change_student_pass (char *username,char *new_password) {
    if (strcmp(logined_user.type,"student")==0) return 2;
    int result = 0;
    user_info check_user;
    FILE *finfo = fopen(user_info_file_name,"r+b");
    while (fread(&check_user,sizeof(user_info),1,finfo)>=1) {
        if (strcmp(username,check_user.user_id)==0) {
            result = 1;
            strcpy(check_user.password,new_password);
            fseek(finfo,(-1)*sizeof(user_info),SEEK_CUR);
            fwrite(&check_user,sizeof(user_info),1,finfo);
            break;
        }
    }
    fclose(finfo);
    return result;
}

#endif //UserManagement.h

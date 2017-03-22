/*
 * prfile.c
 *
 *  Created on: 19 марта 2017 г.
 *      Author: walery
 */


#include "profile.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "parson/parson.h"


//-------------- defs


//-----------------  Vars

static struct profile_t * _profile;


static const char* profile_file_name = "profile.json";
static const char* profile_file_path = "profile";

JSON_Array * jarray;

static JSON_Value *root_value;
static JSON_Object *root_object;

static char *serialized_string = NULL;

//------------------- Functions

// Проверка загрузки
static void
_check_root_value(){
	char *serialized_string = NULL;

	serialized_string = json_serialize_to_string_pretty(root_value);


	puts("========");
	puts(serialized_string);

	json_free_serialized_string(serialized_string);

}





/**
 * Загрузка файла профилей.
 */
static int
_load_profile(void){

	int result=0;

	char  path[128] = {NULL};

	strcat(path,profile_file_name);

	root_value = json_parse_file_with_comments(path);

//	_check_root_value();

	return (root_value==NULL?0:1);

}

void save_profile(void){

}

void new_profile(void){

}

void delete_profile(void){

}

static void
_serialization_example(FILE* fp)
{


	json_object_set_string(root_object, "name", "John Smith");
	json_object_set_number(root_object, "age", 25);
	json_object_dotset_string(root_object, "address.city", "Cupertino");
	json_object_dotset_value(root_object, "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));
	serialized_string = json_serialize_to_string_pretty(root_value);

	fputs(serialized_string,fp);



}


static int
_check_profile_file_existence()
{
	int rval;
	char  path[128] = {NULL};


//	strcat(path ,profile_file_path);
//	strcat(path,"/");
	strcat(path,profile_file_name);

	 /* Check file existence. */
	 rval = access (path, F_OK);
	 if (rval == 0)
	  printf ("%s exists\n", path);
	 else {
	  if (errno == ENOENT)
	   printf ("%s does not exist\n", path);
	  else if (errno == EACCES)
	   printf ("%s is not accessible\n", path);
	  return (errno);
	 }
	 return (0);
}

static void
write_str(char* str){
	JSON_Status status;
	JSON_Value *value = json_value_init_object();
	char *serialized_string = NULL;

	FILE *fp;
	fp = fopen("test.txt", "w+");
	fputs(str,fp);
	fclose(fp);



	value = json_parse_file_with_comments("test.txt");
	serialized_string = json_serialize_to_string_pretty(value);
	json_serialize_to_file(value,"user_data.json");

//	status = json_serialize_to_file(str, "user_data.json");
//	printf("status:%d",status);
}

/***
 * Создать профиль по-умолчанию.
 */
static void
_create_profile(FILE *fp)
{
//	JSON_Value *root_value = json_value_init_object();
//	JSON_Object *root_object = json_value_get_object(root_value);
	JSON_Array *root_array;

	char *serialized_string = NULL;

	char* path = "profiles";

	char *prof1 = "[]";
	char* prof3 = "{\"profile1\":{\"name\": \"profile1\",\"description\": \"Reprap mendel with X,Y axes by belt, Z axe with two shafts. Extruder.\","
			"\"file\": \"profile1.json\",\"default\" : true}}";
	char* prof4 = "{\"profile2\":{\"profile2\": \"profile2\",\"description\": \"Reprap mendel with X,Y axes by belt, Z axe with two shafts. Extruder.\","
			"\"file\":\"profile2.json\",\"default\" : false}}";

	json_object_set_value(root_object,path,json_parse_string(prof1));

	root_array = json_object_get_array(root_object,"profiles");
	json_array_append_value(root_array,json_parse_string(prof3));
	json_array_append_value(root_array,json_parse_string(prof4));

	serialized_string = json_serialize_to_string_pretty(root_value);

	fputs(serialized_string,fp);

	puts("========");
	puts(serialized_string);

	json_free_serialized_string(serialized_string);

//	json_value_free(root_value);
}




static int
_deserialize(void)
{
	int result=0;

	char  path[128] = {NULL};

	strcat(path,profile_file_name);

	root_value = json_parse_file_with_comments(path);



	return (result);
}


static int
_deserialize1(void)
{
	char  filename[128] = {NULL};

	int result = NULL;
	uint i;

	strcat(filename,profile_file_name);

	volatile JSON_Array  * array;

	JSON_Value *  rvalue;	// key
	JSON_Object* robject;

	JSON_Value *  value;	// model
	JSON_Object *object;

	value = json_parse_file_with_comments("test.txt");


	object = json_value_get_object(value);

	rvalue = json_parse_string("{\"emails\":\"\"}");

JSON_Array *arr3 = json_value_get_array(rvalue);

	///////////////////
    //////////////////
	char* _name = "contact";
	char* _name2 = "emails";

	array = json_value_get_array(value);

	JSON_Array* arr5 = json_object_dotget_array(object,"contact.emails");


//	result = json_array_get_count(array);
	for(i=0;i<json_array_get_count(arr5);i++){
//		eml = json_array_get_object(varray,i);
		printf("%10s \n",json_array_get_string(arr5,i));
	}


	return result;
}


/**
 * Создать переменные и загрузить файл Профилей.
 * Проверка наличия файла профиля и его правильность или
 * создать новый профиль профиль по-умолчанию.
 */
void init_profile(void){

	char  filename[128] = {NULL};

	FILE *fp;

//	struct profile_t * _profile;

//	_profile = (struct profile_t*)malloc(sizeof(struct profile_t));

	strcat(filename,profile_file_name);

	root_value = json_value_init_object();
	root_object = json_value_get_object(root_value);

	if(_check_profile_file_existence()){
		fp = fopen(filename, "w+");

		_create_profile(fp);

		fclose(fp);

		printf("file %s created.\n",filename);
	}else{
//		fp = fopen(filename, "r+");
		printf("file %s exist.\n", filename);
		_load_profile();
	}




//	_serialization_example(fp);



//	_deserialize();


//	free(_profile);

}

void
destroy_profile(void)
{
	json_value_free(root_value);
}






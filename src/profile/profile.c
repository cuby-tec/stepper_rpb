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


//Reprap mendel with X,Y axes by belt, Z axe with two shafts. Extruder.
static const char* profiledDescription_1 = "Profile with 5 axes[X,Y,Z(2),E.]";
//profile2.json
static const char* profileFilename_1 = "profile1.prf";

//static const char* _default = "true"

static JSON_Array *root_array;



//-------------------

static struct profile_t * _profile;


static const char* profile_file_name = "profiles.json";	// Список профилей
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

/**
 * проверка наличия файла - Списка профилей.
 */
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


/**
 * построение описанисателей профилей для файла - Список профилей.
 */
//static char* templ1 = "{\"profile1\":{\"name\":";
//static char* templ2 = "\"description\":";
//static char* templ3  = "\"file\":";

const char* startobj = "{";
const char* endobj = "}";
const char* colon = ":";
const char* comma = ",";
const char* escape1 =  "\"";
const char* templ_root_array = "[]";

const char* templ_root_path = "profiles";
const char* templ_field_profile = "profile";
const char* templ_name = "name";
const char* templ_description = "description";
const char* templ_file = "file";
const char* templ_default = "default";
const char* templ_true = "true";
const char* templ_false = "false";

//profile1
static const char* profileName_1 = "Profile";


static size_t names_counter = 0;



static size_t size_buffer = 50;
static char* name_buffer;

static char*
_new_profile_name()
{
//	char* number;
//	char str[256];
//	char buffer[size_buffer];

	 int nchars;

//	buffer = (char *) malloc (size);

//	 if (buffer == NULL)
//		 return NULL;


//	strcpy(new_name,profileName_1);
//	snprintf(str, sizeof str, "%zu", names_counter);
	 names_counter++;
	nchars = snprintf (name_buffer, size_buffer,"%s%zu",profileName_1,names_counter);

	if(nchars < size_buffer)
		return name_buffer;
	else
		return NULL;
}


#define PROFILE_BUFFER_SiZE	1024

static char buffer[PROFILE_BUFFER_SiZE];

static char*_build_profile_record(int isDefault ){
//	char result[1024] = {NULL};
	char* result = buffer;

	result[0] = 0;

	strcat(result,startobj);
	strcat(result,escape1);
	strcat(result,templ_field_profile); //
	strcat(result,escape1);
	strcat(result,colon);

	strcat(result,startobj);
	strcat(result,escape1);
	strcat(result,templ_name);
	strcat(result,escape1);
	strcat(result,colon);
	strcat(result,escape1);
//	strcat(result,profileName_1);
	name_buffer = (char*)malloc(size_buffer);
	if(name_buffer){
		strcat(result,_new_profile_name());
		free(name_buffer);
	}
	else
		return NULL;
	strcat(result,escape1);
	strcat(result,comma); // name


	strcat(result,escape1);
	strcat(result,templ_description);
	strcat(result,escape1);
	strcat(result,colon);
	strcat(result,escape1);
	strcat(result,profiledDescription_1);
	strcat(result,escape1);
	strcat(result,comma);
	strcat(result,escape1);
	strcat(result,templ_file);
	strcat(result,escape1);
	strcat(result,colon);
	strcat(result,escape1);
	strcat(result,profileFilename_1);
	strcat(result,escape1);

	strcat(result,comma);
	strcat(result,escape1);
	strcat(result,templ_default);
	strcat(result,escape1);
	strcat(result,colon);
	strcat(result,escape1);
	if(isDefault)
		strcat(result,templ_true);
	else
		strcat(result,templ_false);
	strcat(result,escape1);
	strcat(result,endobj);
	strcat(result,endobj);

	return (buffer);
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

	root_object = json_value_get_object(root_value);

	root_array = json_object_get_array(root_object,templ_root_path);

//	_check_root_value();

	return (root_value==NULL?0:1);

}



/***
 * Создать профиль по-умолчанию.
 */
static void
_create_profile(FILE *fp)
{
//	JSON_Value *root_value = json_value_init_object();
//	JSON_Object *root_object = json_value_get_object(root_value);

	char *serialized_string = NULL;


/*
	char* prof3 = "{\"profile\":{\"name\": \"profile1\",\"description\": \"Reprap mendel with X,Y axes by belt, Z axe with two shafts. Extruder.\","
			"\"file\": \"profile1.json\",\"default\" : false}}";

	char* prof4 = "{\"profile\":{\"name\": \"profile2\",\"description\": \"Reprap mendel with X,Y axes by belt, Z axe with two shafts. Extruder.\","
			"\"file\":\"profile2.json\",\"default\" : false}}";

	char* prof5 = _build_profile_record(1);
*/
	root_object = json_value_get_object(root_value);

	json_object_set_value(root_object,templ_root_path,json_parse_string(templ_root_array));
//	root_array = json_object_get_array(root_object,"profiles");
	root_array = json_object_get_array(root_object,templ_root_path);

	char* prof_n;


	prof_n = _build_profile_record(1);
	json_array_append_value(root_array,json_parse_string(prof_n)); //prof3
//	free(prof_n);

	prof_n = _build_profile_record(0);
	json_array_append_value(root_array,json_parse_string(prof_n));
//	free(prof_n);

	prof_n = _build_profile_record(0);
	json_array_append_value(root_array,json_parse_string(prof_n));
//	free(prof_n);

	serialized_string = json_serialize_to_string_pretty(root_value);

	fputs(serialized_string,fp);

//	puts("========");
//	puts(serialized_string);

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
//	root_object = json_value_get_object(root_value);

	if(_check_profile_file_existence()){
		fp = fopen(filename, "w+");

		_create_profile(fp);

		fclose(fp);

		printf("file %s created.\n",filename);
	}else{
//		fp = fopen(filename, "r+");
		if( _load_profile())
			printf("file %s exist.\n", filename);
		//todo if profiles not loaded.
	}
//	_serialization_example(fp);
//	_deserialize();
//	free(_profile);
}


//prfl_StringArray*
void  prfl_getListPrflNames(prfl_StringArray* dst){
//	prfl_StringArray * names = (prfl_StringArray*)dst;
	// Считаем, что профиль загружен успешно.
	size_t i;
	JSON_Object* obj;
	char* name;
	// ini dst
	prfl_init_array(dst);
	// circle by JASON_Array
	size_t count = json_array_get_count(root_array);
	for(i=0;(i<count)&&(dst->index<dst->length);i++){
		obj =  json_array_get_object(root_array,i);
		name = json_object_dotget_string(obj,"profile.name");
		prfl_add_element(dst,name);
		printf("prfl_getListPrflNames[424]:%s\n",name);
	}


//	return (prfl_names);
}



void
destroy_profile(void)
{
	json_value_free(root_value);
}






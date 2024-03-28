#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <dirent.h>
#include<bits/stdc++.h>
using namespace std;
int match_num;
#define MAX_ROWS 1000
#define HASH_SIZE 8388608
int number_snp;
struct DictionaryNode {
    char key[20];    // �����ַ�������󳤶�Ϊ50
    char k0[20];
    char *value;
};
struct DictionaryNode dictionary[1000];
//ʵ������ָ����snpλ�����������
typedef struct {
    char snp_code[40];
    char snp_info[40];
    char left_reads1[150];
    char right_reads2[150];
    char cnt[10];
} SNPData;

// �����ϣ��ڵ�
typedef struct HashNode {
    char snp_code[40];
    char snp_info[40];
    int location;

    struct HashNode* next;  // ָ����һ���ڵ��ָ��
} HashNode;


// �����ϣ��
HashNode* hash_table1[HASH_SIZE];
HashNode* hash_table2[HASH_SIZE];
HashNode* hash_table3[HASH_SIZE];
HashNode* hash_table4[HASH_SIZE];



// //����ת��
int convert_to_binary_P(const char* sequence) {
    // ������Ļ���������ת��Ϊ�����ƣ���ת��Ϊʮ����  P��������
    char binary[100] = "";
    int i;
    for (i = 0; i < strlen(sequence); i++) {
        char ch = sequence[i];

        if (ch == 'N' or ch=='n') {
            char base_list[] = {'A', 'T', 'C', 'G'};
            int random_index = rand() % 4;
            ch = base_list[random_index];
        }

        if (ch == 'A' or ch=='a') {
            strcat(binary, "00");
        } else if (ch == 'T' or ch=='t') {
            strcat(binary, "01");
        } else if (ch == 'C' or ch=='c') {
            strcat(binary, "10");
        } else if (ch == 'G' or ch=='g') {
            strcat(binary, "11");
        } else {
            return -1;
        }
    }
    //����ʮ��������
    return strtol(binary, NULL, 2);
}

//��ȡSNPλ����Ϣ����
SNPData* read_excel() {
    SNPData* data = (SNPData*)malloc(MAX_ROWS * sizeof(SNPData));
    SNPData* res = (SNPData*)malloc(sizeof(SNPData));

    FILE *file;
    char line[400];
    char *token;
    char *columns[4];
    int columnCount;

    //��CSV�ļ�
    file = fopen("NewSNP.csv", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return NULL;
    }

    int i=0;

    // ���ж�ȡCSV�ļ�
    while (fgets(line, sizeof(line), file)) {
        columnCount = 0;

        // ʹ��strtok�����ָ�ÿһ�е�������
        token = strtok(line, ",");

        while (token != NULL && columnCount < 4 ) {
            columns[columnCount++] = token;

            // �����ָ���һ��������
            token = strtok(NULL, ",");
        }
        strcpy(res->snp_code, columns[0]);
        strcpy(res->snp_info, columns[1]);
        if(i!=0){
            strcpy(dictionary[i].key, columns[1]);
        strcpy(dictionary[i].k0, columns[0]);
        }
        strcpy(res->left_reads1, columns[2]);
        strcpy(res->right_reads2, columns[3]);
        data[i] = *res;
   	//  printf("%s,%s,%s,%s\n",data[i].snp_code,data[i].snp_info,data[i].left_reads1,data[i].right_reads2);
        number_snp++;
        
        i++;
    }
    //�ر��ļ�
    // cout<<number_snp<<endl;
    fclose(file);

    return data;
}



//��ϣ��Ľ���
void process_SNP() {
    SNPData* snp_data = read_excel();
    int i;

    int snp_binary_1;
    int snp_binary_2;
    int snp_binary_3;
    int snp_binary_4;

    char* snp_code;
    char* snp_info;
    char* left_reads1;
    char* right_reads2;

    char substring_1_qian_1[match_num+1];
 
    char substring_1_hou_1[match_num+1];

    HashNode* res1 = NULL;
    HashNode* res2 = NULL;
    HashNode* res3 = NULL;
    HashNode* res4 = NULL;
    HashNode* res5 = NULL;
    HashNode* res6 = NULL;
    HashNode* res7 = NULL;
    HashNode* res8 = NULL;
    for (i = 1; i <number_snp; i++) {
        res1 = (HashNode*)malloc(sizeof(HashNode));
        res2 = (HashNode*)malloc(sizeof(HashNode));
        res3 = (HashNode*)malloc(sizeof(HashNode));
        res4 = (HashNode*)malloc(sizeof(HashNode));
        res5 = (HashNode*)malloc(sizeof(HashNode));
        res6 = (HashNode*)malloc(sizeof(HashNode));
        res7 = (HashNode*)malloc(sizeof(HashNode));
        res8 = (HashNode*)malloc(sizeof(HashNode));
        snp_code = snp_data[i].snp_code;
        snp_info = snp_data[i].snp_info;
        left_reads1 = snp_data[i].left_reads1;
        right_reads2 = snp_data[i].right_reads2;

        int index_1 = strchr(left_reads1, '[') - left_reads1;
        int index_2 = strchr(right_reads2, '[') - right_reads2;
        int index_3 = strchr(left_reads1, ']') - left_reads1;
        int index_4 = strchr(right_reads2, ']') - right_reads2;
        strcpy(res1->snp_code, snp_code);
        strcpy(res1->snp_info, snp_info);
        strcpy(res2->snp_code, snp_code);
        strcpy(res2->snp_info, snp_info);
        strcpy(res3->snp_code, snp_code);
        strcpy(res3->snp_info, snp_info);
        strcpy(res4->snp_code, snp_code);
        strcpy(res4->snp_info, snp_info);
        strcpy(res5->snp_code, snp_code);
        strcpy(res5->snp_info, snp_info);
        strcpy(res6->snp_code, snp_code);
        strcpy(res6->snp_info, snp_info);
        strcpy(res7->snp_code, snp_code);
        strcpy(res7->snp_info, snp_info);
        strcpy(res8->snp_code, snp_code);
        strcpy(res8->snp_info, snp_info);

        //����

        if (index_1 != -1 && index_1 - match_num >= 0 && index_3 != -1 && strlen(left_reads1) - index_3 - match_num - 1 >= 0) {
            strncpy(substring_1_qian_1, left_reads1 + index_1 - match_num, match_num);

            strncpy(substring_1_hou_1, left_reads1 + index_3 + 1, match_num);
 

            substring_1_qian_1[match_num] = '\0';

            substring_1_hou_1[match_num] = '\0';


            snp_binary_1 = convert_to_binary_P(substring_1_qian_1);

            snp_binary_3 = convert_to_binary_P(substring_1_hou_1);

//             printf("%d\n",snp_binary_2);
            res1->location = 1;
            res1->next = NULL;

            //������һ��
            if(hash_table1[snp_binary_1] == NULL){
                hash_table1[snp_binary_1] = res1;
            } else{
                res1->next = hash_table1[snp_binary_1];
                hash_table1[snp_binary_1] = res1;
            }

            //�����ڶ���

            res3->location=1;
            res3->next=NULL;
            //������һ��
            if(hash_table3[snp_binary_3] == NULL){
                hash_table3[snp_binary_3] = res3;
            } else{
                res3->next = hash_table3[snp_binary_3];
                hash_table3[snp_binary_3] = res3;
            }


            //�����ڶ���
// 			printf("%s %s\n",hash_table2[snp_binary_2]->snp_code,hash_table2[snp_binary_2]->snp_info);
// 			printf("%d\n",i);
        }
        //����
        if (index_2 != -1 && index_2 - match_num >= 0 && index_4 != -1 && strlen(right_reads2) - index_4 - match_num - 1 >= 0) {

            strncpy(substring_1_qian_1, right_reads2 + index_1 - match_num, match_num);

            strncpy(substring_1_hou_1, right_reads2 + index_3 + 1, match_num);
  

            substring_1_qian_1[match_num] = '\0';

            substring_1_hou_1[match_num] = '\0';


            snp_binary_1 = convert_to_binary_P(substring_1_qian_1);

            snp_binary_3 = convert_to_binary_P(substring_1_hou_1);
 

            res5->location = 2;
            res5->next = NULL;

            //������һ��
            if(hash_table1[snp_binary_1]==NULL){
                hash_table1[snp_binary_1]=res5;
            } else{
                res5->next = hash_table1[snp_binary_1];
                hash_table1[snp_binary_1] = res5;
            }
            
            res7->location = 2;
            res7->next=NULL;
            //������һ��
            if(hash_table3[snp_binary_3]==NULL){
                hash_table3[snp_binary_3]=res7;
            } else{
                res7->next = hash_table3[snp_binary_3];
                hash_table3[snp_binary_3] = res7;
            }

        }
        res1=NULL;
        res2=NULL;
        res3=NULL;
        res4=NULL;
        res5=NULL;
        res6=NULL;
        res7=NULL;
        res8=NULL;
    }
            // for (int i = 0; i <HASH_SIZE; i++)
            // {
            //     if (hash_table1[i] != NULL) {
            // printf("%d========\n",i);
            // getchar();
            //     }
            // }
}
char rep(char s){
    if(s=='A')
    return 'T';
        if(s=='T')
    return 'A';
        if(s=='C')
    return 'G';
        if(s=='G')
    return 'C';
}

// ���ݻ������в��ҹ�ϣ��ڵ�
void find_hash_node(const std::string& fastqFilePath, const std::string& resName, int snp_num) {
    // ����ȡȫ���������е� data ����
    // Ԥ����������и�ʽ
    cout<<"���ڴ���=========="<<resName<<endl;
    int hash_number1, hash_number2, hash_number3, hash_number4;

    char *temp1=(char *)malloc(sizeof(char)*(1+match_num));
    char *temp2=(char *)malloc(sizeof(char)*(1+match_num));
    std::unordered_map<std::string, std::string> columns;
    char snp_code[20];//��ʱ�洢��ϣ���ڴ洢��SNPλ����Ϣ
    char snp_info[20];
    char snp_code_else[20];//��ʱ�洢��ϣ���ڴ洢��SNPλ����Ϣ
    char snp_info_else[20];
    HashNode* snp_data1 = (HashNode*)malloc(sizeof(HashNode));
    HashNode* snp_data2 = (HashNode*)malloc(sizeof(HashNode));
    HashNode* snp_data3 = (HashNode*)malloc(sizeof(HashNode));
    HashNode* snp_data4 = (HashNode*)malloc(sizeof(HashNode));
    std::ifstream file(fastqFilePath); // �� CSV �ļ�
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�xxxxxxxx" << std::endl;
        return;
    }

    std::ofstream outFile("output/" + resName + "_table1.csv"); // ��������ļ�
    if (!outFile.is_open()) {
        std::cerr << "�޷������ļ�" << std::endl;
        return;
    }

    outFile << "snp code,snp info,ip, ͻ��λ�ü��,ͻ��λ��,������" << std::endl;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        std::getline(iss, key, ',');
        std::getline(iss, value, ',');

        columns[key] = value;

        std::string code = key;
        std::string data = value;
        int length = data.length();
        // cout<<length<<endl;
  for (int i = 0; i <= length - match_num*2-1&&length>=match_num*2+1; i++) {
   
        data.substr(i, match_num).copy(temp1, match_num, 0);
        temp1[match_num] = '\0';
   
            hash_number1 = convert_to_binary_P(temp1);

            
            if (hash_table1[hash_number1] != NULL) {
            // printf("%d========\n",hash_number1);
            // cout<<"===================1"<<endl;
                snp_data1 = hash_table1[hash_number1];
                while (snp_data1 != NULL) {
                    strcpy(snp_code, snp_data1->snp_code);
                    strcpy(snp_info, snp_data1->snp_info);
                    data.substr(i + match_num+1, match_num).copy(temp2, match_num, 0);
                    temp2[match_num] = '\0';
                    hash_number2 = convert_to_binary_P(temp2);
                    if (hash_table3[hash_number2] != NULL) {
// ======================
                    
                        // cout<<"===================2"<<endl;
                        snp_data2 = hash_table3[hash_number2];
                        while (snp_data2 != NULL) {
                            strcpy(snp_code_else, snp_data2->snp_code);
                            strcpy(snp_info_else, snp_data2->snp_info);
                            if(!strcmp(snp_code, snp_code_else)&&!strcmp(snp_info, snp_info_else)){
// ======================
                                                    int k;
                                                    char charStr[2];
                                                    for (k = 0; k <number_snp; k++) {
                                                        if (!strcmp(dictionary[k].key,snp_info_else)) {
                                                            if (snp_data2->location == 1) {
                                                                charStr[0] = (char)toupper(data[i + match_num]);
                                                            }
                                                            if (snp_data2->location == 2) {
                                                                charStr[0] = rep((char)toupper(data[i + match_num]));
                                                            }
                                                            charStr[1] = '\0';
                                                            break;
                                                        }
                                                    }
                                                    if (strlen(dictionary[k].value) < snp_num) {
                                                        strcat(dictionary[k].value, charStr);
                                                        if (snp_data2->location == 1) {
                                                            // cout<<"==================="<<endl;
                                                            outFile << snp_code_else << "," << snp_info_else << "," << code << "," << (char)toupper(data[i + match_num])<< "," << i + match_num << "," << snp_data2->location << std::endl;
                                                        }
                                                        if (snp_data2->location == 2) {
                                                            // cout<<"==================="<<endl;
                                                            outFile << snp_code_else << "," << snp_info_else << "," << code << "," << rep((char)toupper(data[i + match_num])) << "," << i + match_num << "," << snp_data2->location << std::endl;
                                                        }
                                                    }
// ======================
                            }
                            snp_data2 = snp_data2->next;
                        }
                    }
                    snp_data1 = snp_data1->next;
                }
            }
        }
    }
    file.close();
    outFile.close();
}


//��ʽ��ʼ��
#define MAX_LINE_LENGTH 1024

void Inithash_table(){
    int i;
    for(i=0;i<HASH_SIZE;i++){
        hash_table1[i]=NULL;
        hash_table2[i]=NULL;
        hash_table3[i]=NULL;
        hash_table4[i]=NULL;
    }
}
struct DictionaryNode* Initdict(int snp_num,struct DictionaryNode * Dictionary){
	int i;
    for (i = 0; i < number_snp; i++)
    {
        strcpy(Dictionary[i].value, "");
        // printf("========%d\n",strlen(dictionary[i].value));
    }
    return Dictionary;
}

void listFiles(int snp_num) {
    DIR *dir;
    struct dirent *entry;
    char folderPath[100]="data_std/";
    dir = opendir(folderPath);

    if (dir == NULL) {
        perror("Error opening folder");
        return;
    }
    

    // ����SNP���ݲ������ϣ��
    
    // printf("Files in %s:\n", folderPath);

    while ((entry = readdir(dir)) != NULL) {
        // cout<<"=====";
        // ����Ƿ�Ϊ�����ļ�
            Initdict(snp_num,dictionary);
            // cout<<entry->d_name<<endl;
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                // cout<<"=====";
            Inithash_table();
            // printf(file);
            // printf("\n");
            size_t length = strlen(entry->d_name);
            int length_temp = length - 11;
            char extracted_part[100]={0};
            strncpy(extracted_part, entry->d_name, length_temp);
            // cout<<extracted_part<<endl;
            char file_output[100];
            sprintf(file_output, "data_std/%s", entry->d_name);

            process_SNP();	
            find_hash_node(file_output,extracted_part,snp_num);

            // table2(entry->d_name);
            Initdict(snp_num,dictionary);
            number_snp=0;
        }
           
    }

    closedir(dir);
}


int main() {
    time_t start, end;
    char file[50];
    ifstream fpara("para.txt");
    if (!fpara.is_open()) {
        std::cerr << "Failed to open file para.txt" << std::endl;
        return 1;
    }
    
    // ��ȡ��һ�в�����
    string line;
    getline(fpara, line);   
    int snp_num;
    // ��ȡ�ڶ�����Ϊnum��ֵ
    if (getline(fpara, line)) {
        snp_num = std::stoi(line);
        std::cout << "Read snp_num from file: " << snp_num << std::endl;
    } else {
        std::cerr << "File para.txt does not contain a second line" << std::endl;
        return 1;
    }
    if (getline(fpara, line)) {
        match_num= std::stoi(line);
        std::cout << "Read match_num from file: " << match_num<< std::endl;
    } else {
        std::cerr << "File para.txt does not contain a third line" << std::endl;
        return 1;
    }
    fpara.close();
    // printf("�����ļ���λ�ã�ע���Ǿ���·����: ");
    // scanf("%s", &file);

    int i;
    for (i = 0; i <1000; i++)
    {
        dictionary[i].value= (char*)malloc((snp_num+5) * sizeof(char));
        strcpy(dictionary[i].value, "");
        // printf("========%d\n",strlen(dictionary[i].value));
    }
    
    start = clock();

    double cpu_time_used;

    listFiles(snp_num);

    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Լ�ֵ�С�����һλ
    double rounded_time = round(cpu_time_used * 10) / 10.0;


    printf("��������ʱ�䣺%.1f ��\n", rounded_time);

    sleep(10);  // ����2�룬���Ը�����Ҫ����
    return 0;
}

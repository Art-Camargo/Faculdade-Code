#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <stdlib.h>


#ifdef _WIN32 
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void clearTerminal(bool ignore) {
    system(CLEAR);
    if (ignore) {
        std::cin.ignore(); 
    }
}

char* toLowerCase(const char* str) {
    size_t length = strlen(str);
    char* lowerStr = new char[length + 1];

    for (size_t i = 0; i < length; ++i) {
        lowerStr[i] = tolower(str[i]);
    }
    lowerStr[length] = '\0'; 
    return lowerStr;
}

class Utils {
public: 
   float getGrade(int n, char* name) {
    float grade;
    bool isValid = true;
    while (isValid) {
        std::cout << "Informe a nota " << n << " (entre 0.00 e 10.00) do aluno " << name << " : " ;
        std::cin >> grade;
        clearTerminal(false);
        if (std::cin.fail() || grade < 0.0f || grade > 10.0f) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cerr << "Nota inválida. Por favor, insira um valor entre 0.00 e 10.00." << std::endl;
        } else {
            isValid = false; 
        }
    }
    clearTerminal(true);
    return grade; 
}

    int getTotalStudents() {
        int total = 0;
        do {
            std::cout << "Informe a quantidade total de alunos: ";
            std::cin >> total;
            clearTerminal(true);
            if (total <= 0) {
                std::cerr << "Informe um valor maior que 0" << std::endl;
            }
        } while(total <= 0);
        return total; 
    }

    char* getStudentName(int num) {
        static char name[40]; 
        std::cout << "Informe o nome do aluno " << num << ": "; 
        if (fgets(name, sizeof(name), stdin) != nullptr) {
            name[strcspn(name, "\n")] = '\0'; 
        }
        return name;
    }

    int getPreviousCode(int prevCode) {
        return prevCode + 1;
    } 
};

class Student {
private:
    char name[40];
    int code;
    std::vector<float> grades;

public:
    void setName(const char* newName) {
        strncpy(name, newName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    const char* getName() const {
        return name;
    }

    void setCode(int newCode) {
        code = newCode;
    }

    int getCode() const {
        return code;
    }

    void setGrades(const std::vector<float>& newGrades) {
        grades = newGrades;
    }

    const std::vector<float>& getGrades() const {
        return grades;
    }

    float getAverage() const {
        if (grades.empty()) {
            std::cerr << "Erro: Não há notas disponíveis para calcular a média." << std::endl;
            return 0.0f;
        }

        float sum = 0.0f;
        for (float grade : grades) {
            sum += grade;
        }
        return sum / grades.size(); 
    }

    char getFinalGrade() const {
        if (this->getAverage() >= 9) return 'A';
        if (this->getAverage() >= 7.5) return 'B';
        if (this->getAverage() >= 6) return 'C';
        return 'D';
    }
};

int main() {
    Utils utils;
    int total = utils.getTotalStudents();
    Student* students = new Student[total];
    for (int i = 0; i < total; ++i) {
        clearTerminal(false);
        char* name = utils.getStudentName(i + 1);
        std::vector<float> grades;
        students[i].setName(name);
        int code = utils.getPreviousCode(i);
        students[i].setCode(code);
        for (int j = 1; j <= 3; ++j) {
            float grade = utils.getGrade(j, name);
            grades.push_back(grade);
        }
        students[i].setGrades(grades);
    }

    std::vector<int> codes;

    for (int h = 0; h < total; h++) {
        int currentCode = students[h].getCode();
        const char* currentName = students[h].getName();
        bool inserted = false;
        for (size_t g = 0; g < codes.size(); g++) {
            if (strcmp(toLowerCase(currentName), toLowerCase(students[g].getName())) < 0) {
                codes.insert(codes.begin() + g, currentCode);
                inserted = true;
                break; 
            }
        }
        if (!inserted) {
            codes.push_back(currentCode);
        }
    }

    
    
    std::cout << "\nDados dos Alunos:\n";
     for (int i = 0; i < codes.size(); ++i) {
        int code = codes[i];
        for (int j = 0; j < total; ++j) {
            if (students[j].getCode() == code) {
                std::cout << "Aluno " << (i + 1) << ":\n";
                std::cout << "Nome: " << students[j].getName() << std::endl;
                std::cout << "Código: " << students[j].getCode() << std::endl;
                std::cout << "Notas: ";
                for (float grade : students[j].getGrades()) {
                    std::cout << grade << " ";
                }
                std::cout << std::endl;
                std::cout << "Média: " << students[j].getAverage() << std::endl;
                std::cout << "Nota Final: " << students[j].getFinalGrade() << std::endl;
                std::cout << std::endl << std::endl;
                break; 
            }
        }
    }

    delete[] students;

    return 0;
}

# 🎓 Student & Exam Management System (C Project)

This project is written in **C** and simulates a simple university management system for:

- students  
- exams  
- course statistics  

The program reads data from text files, updates students’ records based on completed exams, sorts the results, and saves the final output into binary files.

---

## 🚀 Main Features

✅ Read students from text file  
✅ Read exams from text file  
✅ Dynamic memory allocation  
✅ Update CFU and weighted average  
✅ Student sorting using **Merge Sort on linked lists**  
✅ Course statistics calculation  
✅ Course statistics sorting using **Merge Sort on arrays**  
✅ Binary file export  
✅ Table-style formatted output  
✅ Manual memory management  

---

## 🧠 Data Structures

- `Studente`
- `Esame`
- `StatCorso`
- Linked lists
- Dynamic arrays

---

## 📂 Input

The program asks for:

1. Username  
2. Students file name  
3. Exams file name  

Example:

filippo  
studenti.txt  
esami.txt  


---

## 📂 Input File Formats

👨‍🎓 Students file (studenti.txt)

each line:
<studentID> <name>@<surname>@<CFU> <weighted average>

Examples:
```txt
1001 Filippo@Rocco@18 27.5
1005 Anna@Ferrari@84 28.10
1010 Chiara@De Angelis@60 26.10
```

📚 Exams file (esami.txt)

each line:
<course>@<grade> <studentID> <university training credits>

Examples:
```txt
Analisi Matematica T-1@23 1001 9
Fondamenti di Informatica T@30 1001 12
Geometria e Algebra T@27 1001 6
```
⚠️ Invalid or corrupted rows are automatically discarded.

---

## 📦 Output

Two binary files are automatically generated:

- `<username>_students.bin`
- `<username>_courses.bin`

They contain:

- updated and sorted students
- sorted course statistics

---

## 🛠 Technologies

- Language: **C**
- IDE: Visual Studio
- Version Control: Git + GitHub
- OS: Windows

---

## ▶ How to Run

1. Clone the repository: 
```bash
git clone <repository-url>
```
 

2. Open the solution in Visual Studio

3. (Optional) Add your own text files (containing exams and students) inside the project folder:
/StudentExamSystem/

4. Build and run

---

## 📊 Student Sorting Criteria

Students are sorted by:

1. Weighted average (descending)
2. CFU (descending)
3. Last name (alphabetical)
4. First name (alphabetical)

Implemented using **Merge Sort on linked lists**.

---

## 📊 Course Statistics Sorting Criteria

Course statistics are sorted by:

1. Average grade (descending)
2. Number of students (descending)

Implemented using **Merge Sort on arrays**.

---

## 🧑‍💻 Author

Filippo Rocco  
Computer Engineering Student  

---

## 📌 Notes

This project was developed for educational purposes to practice:

- memory management
- data structures
- file I/O
- modular programming
- GitHub workflow

---

## 🌱 Future Improvements

- GUI
- Student search
- CSV support
- Database integration
- Automated testing

---

⭐ If you find this useful, feel free to star the repository!
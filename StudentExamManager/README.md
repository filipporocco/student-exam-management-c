# ?? Student & Exam Management System (C Project)

This project is written in **C** and simulates a simple university management system for:

- students  
- exams  
- course statistics  

The program reads data from text files, updates students’ records based on completed exams, sorts the results, and saves the final output into binary files.

---

## ?? Main Features

? Read students from text file  
? Read exams from text file  
? Dynamic memory allocation  
? Update CFU and weighted average  
? Student sorting using **Merge Sort on linked lists**  
? Course statistics calculation  
? Binary file export  
? Table-style formatted output  
? Manual memory management  

---

## ?? Data Structures

- `Studente`
- `Esame`
- `StatCorso`
- Linked lists
- Dynamic arrays

---

## ?? Input

The program asks for:

1. Students file name  
2. Exams file name  
3. Username  

Example:

studenti.txt
esami.txt
filippo


---

## ?? Output

Two binary files are automatically generated:

- `<username>_students.bin`
- `<username>_courses.bin`

They contain:

- updated and sorted students
- course statistics

---

## ?? Technologies

- Language: **C**
- IDE: Visual Studio
- Version Control: Git + GitHub
- OS: Windows

---

## ? How to Run

1. Clone the repository:

git clone <repository-url>


2. Open the project in Visual Studio

3. Build and run

---

## ?? Student Sorting Criteria

Students are sorted by:

1. Average grade (descending)
2. CFU (descending)
3. Last name (alphabetical)
4. First name (alphabetical)

Implemented using **Merge Sort on linked lists**.

---

## ????? Author

Filippo Rocco  
Computer Engineering Student  

---

## ?? Notes

This project was developed for educational purposes to practice:

- memory management
- data structures
- file I/O
- modular programming
- GitHub workflow

---

## ?? Future Improvements

- GUI
- Student search
- CSV support
- Database integration
- Automated testing

---

? If you find this useful, feel free to star the repository!
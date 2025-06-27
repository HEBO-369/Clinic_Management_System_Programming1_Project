# 🏥 Clinic Management System

A simple clinic management system implemented in C as a part of the **CS121: Computer Programming 1** course at Alexandria University.

This system allows patients to sign up, log in, view doctors, and search for a specific medical specialty. It reads and stores data for both doctors and patients using files and basic data structures like arrays and structs.

## 📌 Features

- 🧑‍⚕️ Load and manage data of **10 doctors** from file  
- 👤 Patients can **sign up** and **log in** (up to 10 patients max)  
- 🔍 **Search** for doctors by specialty  
- 📋 **View all doctors** with full information  
- 🔒 Validations for login, signup limits, and data integrity  

## 🗂️ Project Structure

```
Clinic-Management-System/
│
├── src/                    # Source code files
│   └── main.c
│
├── data/                   # Data files
│   ├── doctors.txt         # Initial doctors' data
│   └── patients.txt        # Dynamic patient data (created after signup)
│
├── report/                 # Documentation (UML, samples, etc.)
│   ├── usecase-diagram.png
│   ├── sequence-diagram.png
│   └── code-snippets.txt
│
├── screenshots/            # Optional: images from program runs
│   └── signup-example.png
│
└── README.md
```

## 🧠 System Logic

- On startup: Load doctor and patient data into memory  
- On signup: Save new patient to memory and file (if < 10 patients)  
- On login: Match credentials with stored data  
- On search: Compare search term with doctors’ specialties  
- On logout: Program ends  

## 📄 Sample Data Format

**doctors.txt**
```
Name:Dr. Alice Johnson	Specialty:Cardiologist	Address:123 Heart Lane, New York, NY	Visita:250.00
Name:Dr. Benjamin Lee	Specialty:Dermatologist	Address:456 Skin Ave, Los Angeles, CA	Visita:180.50

...
```

**patients.txt**
```
name:mohamed	user:mo123	pw:12345
name:ahmed	user:ahmed	pw:1234
...
```

## 🎮 Example Use Case

### Example 1
1. User signs up  
2. User views all doctors  
3. User searches for "Cardiology"  
4. User logs out  

### Example 2
1. User tries to sign in without registering  
2. System redirects them to signup  

## 📷 Screenshots

> You can find them in Screenshots folder  

## ⚙️ Technologies Used

- C Programming Language  
- File Handling  
- Structs and Arrays  

## 📌 Course Info

- **Course**: CS121 – Computer Programming 1  
- **Instructor**: Eng/ Veronica Romany 
- **Team**:
	-Mohamed Wahban
	-Omar Ahmed
	-Mohemed Abdallah
	-Mohamed Gomaa

## 📌 Notes

- The project limits doctors and patients to 10 each.  
- All inputs are validated for correctness.  
- No external libraries were used.  
- Code and documentation were developed fully by the team as per course policy.  

## 🧠 Author

**Mohamed Wahban**  
Student at Alexandria University – Computer & Systems Engineering  
GitHub: [https://github.com/HEBO-369](https://github.com/HEBO-369)

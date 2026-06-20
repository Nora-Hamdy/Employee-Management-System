# 👥 Employee Management System (C++)

![C++](https://img.shields.io/badge/language-C++-blue)

A console-based Employee Management System built using clean architecture
principles and layered design.

## 📑 Table of Contents

- [🏗 Architecture Overview](#-architecture-overview)
- [🧩 Design Patterns Used](#-design-patterns-used)
- [🔄 Operation Result Pattern](#-operation-result-pattern)
- [🛠 Technologies Used](#-technologies-used)
- [🧠 Concepts Used](#-concepts-used)
- [🖥 UI & Data Storage](#-ui--data-storage)
- [✨ Features](#-features)
- [🗂 Project Structure](#-project-structure)
- [🚀 Running the Project](#-running-the-project)
- [📌 Purpose](#-purpose)
- [📄 License](#-license)

## 🏗 Architecture Overview

The project follows a clear separation of concerns:

- **Models**: Core domain entities (Employee, Date)
- **Interfaces**: Abstractions for repository and services
- **Repository Layer**: Data access logic
- **Service Layer**: Business rules and validations
- **UI Layer**: Console-based user interaction
- **Common**: Shared helpers such as operation results and statuses
- **Helpers**: Configuration management and console helpers

## 🧩 Design Patterns Used
- Repository Pattern
- Service Pattern
- Singleton Pattern (Config Manager)

## 🔄 Operation Result Pattern

All operations return a unified `OperationResult` structure that contains:
- Operation status (Success, Failure, NoChanges)
- Optional message
- Optional data

This ensures consistent error handling and messaging across layers.

## 🛠 Technologies Used

- C++17
- STL (Standard Template Library)

## 🧠 Concepts Used

- Object-Oriented Design (OOP)
- Clean Architecture
- Layered architecture with separation of concerns

## 🖥 UI & Data Storage

- Console-based user interface
- File-based persistence using text files

## ✨ Features

- Add, update, delete, and search employees
- Compute net salary and average salaries
- Clear console-based UI with structured output
- Config-driven data file management
- Strong input validation and user feedback

## 🗂 Project Structure
```text
Employee Management System/
│
├── src/                      # Application source code
│   ├── core/                 # Core domain and business logic
│       └── models/           # Domain models implementation
│   ├── helpers/              # Utility implementations
│   ├── repository/           # Data access layer implementation
│   ├── services/             # Application services implementation
│   └── ui/                   # Console-based UI implementation
│
├── include/                  # Header files and public interfaces
│   ├── core/                 # Core domain definitions
│       ├── common/           # Shared types and common headers
│       ├── interfaces/       # Abstract interfaces (contracts)  
│       └── models/           # Domain models declarations   
│   ├── helpers/              # Utility declarations
│   ├── repository/           # Repository declarations
│   ├── services/             # Service declarations
│   └── ui/                   # UI declarations
│
├── config/                   # Application configuration
│   ├── config.txt            # Configuration settings (key-value pairs)
│
├── data/                     # Application data storage
│   ├── employees.txt         # Employee data source
│
├── main.cpp                  # Application entry
├── .gitignore               
├── .gitattributes
├── LICENSE                   # MIT License
└── README.md                 # Project documentation
```

## 🚀 Running the Project

The project is a console-based C++ application and can be built and run using any standard C++17 compiler or higher.

## 📌 Purpose

- Demonstrate a clean and maintainable C++ project structure  

- Apply layered architecture and separation of concerns

- Practice enterprise-style design patterns (Service / Repository)

## 📄 License

MIT License

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum limits for various entities such as doctors, patients, medications, and appointments
#define MAX_DOCTORS 100       // Maximum number of doctors allowed in the system
#define MAX_PATIENTS 300      // Maximum number of patients the system can handle
#define MAX_MEDICATIONS 10    // Maximum number of medications a single patient can have
#define MAX_APPOINTMENTS 100  // Maximum number of appointments that can be scheduled
#define MAX_STAFF 100         // Maximum number of staff members that can be added to the system

// Structure to represent an appointment

/*
 * Structure to represent an appointment.
 * This struct stores information related to an appointment, including:
 * - patientID: The ID of the patient associated with the appointment.
 * - doctorID: The ID of the doctor associated with the appointment.
 * - appointmentDate: The date of the appointment in the format YYYY-MM-DD.
 */

typedef struct {
    int patientID;                  // ID of the patient associated with the appointment
    int doctorID;                   // ID of the doctor associated with the appointment
    char appointmentDate[20];       // Appointment date in the format YYYY-MM-DD
} Appointment;

// Global array to store appointments and a counter to track the total number of appointments
Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

// Structure to represent medication details

/*
 * Structure to represent medication details.
 * This struct stores details about a medication, including:
 * - name: The name of the medication (e.g., Paracetamol).
 * - dosage: The dosage of the medication (e.g., 500mg).
 */

typedef struct {
    char name[100];  // Name of the medication
    char dosage[50]; // Dosage of the medication
} Medication;

// Structure to store information about doctors

/*
 * Structure to store information about doctors.
 * This struct stores details about a doctor, including:
 * - name: The doctor's name (e.g., Dr. Smith).
 * - age: The doctor's age (e.g., 45).
 * - specialty: The doctor's area of specialization (e.g., Cardiologist).
 * - visitingFees: The fee charged by the doctor for consultation (e.g., 200).
 */

typedef struct {
    char name[100];      // Doctor's name, used as a unique identifier
    int age;             // Doctor's age
    char specialty[100]; // Doctor's area of specialization
    int visitingFees;    // Fee charged by the doctor for consultation
} Doctor;

// Structure to store information about patients

/*
 * Structure to store information about patients.
 * This struct stores details about a patient, including:
 * - name: The patient's name (e.g., John Doe).
 * - age: The patient's age (e.g., 30).
 * - diagnosis: The patient's medical condition or diagnosis (e.g., Flu).
 * - roomNumber: The room number assigned to the patient (e.g., 101).
 * - doctorID: The ID of the doctor treating the patient (e.g., 2).
 * - medications: An array of medications assigned to the patient.
 * - medicationCount: A counter to track the number of medications assigned to the patient.
 */

typedef struct {
    char name[100];            // Patient's name
    int age;                   // Patient's age
    char diagnosis[100];       // Patient's diagnosis or medical condition
    int roomNumber;            // Room number assigned to the patient
    int doctorID;              // ID of the doctor treating the patient
    Medication medications[MAX_MEDICATIONS]; // List of medications assigned to the patient
    int medicationCount;       // Counter to track the number of medications assigned
} Patient;

// Structure to define shifts for staff members

/*
 * Structure to define shifts for staff members.
 * This struct stores details about a shift for a staff member, including:
 * - day: The day of the week the shift is scheduled (e.g., Monday, Tuesday).
 * - startTime: The start time of the shift (e.g., 09:00 AM).
 * - endTime: The end time of the shift (e.g., 05:00 PM).
 * - role: The role assigned during the shift (e.g., Nurse, Admin).
 */

typedef struct {
    char day[20];         // Day of the week for the shift (e.g., Monday, Tuesday)
    char startTime[10];   // Start time of the shift (e.g., 09:00)
    char endTime[10];     // End time of the shift (e.g., 17:00)
    char role[50];        // Role assigned during the shift (e.g., Nurse, Admin)
} Shift;

// Structure to store information about staff members

/*
 * Structure to store information about staff members.
 * This struct stores details about a staff member, including:
 * - name: The name of the staff member (e.g., Alice Johnson).
 * - role: The role of the staff member (e.g., Nurse, Admin).
 * - contactInfo: The contact information for the staff member (e.g., phone number or email).
 * - schedule: An array of shifts assigned to the staff member.
 * - shiftCount: A counter to track the number of shifts assigned to the staff member.
 */

typedef struct {
    char name[100];          // Name of the staff member
    char role[50];           // Role of the staff member (e.g., Nurse, Admin)
    char contactInfo[100];   // Contact information (e.g., phone or email)
    Shift schedule[MAX_APPOINTMENTS]; // Array to hold the staff member's shift schedule
    int shiftCount;          // Counter to track the number of shifts assigned
} Staff;

// Global arrays to store doctors, patients, and staff
Doctor doctors[MAX_DOCTORS];      // Array to store doctor information
Patient patients[MAX_PATIENTS];  // Array to store patient information
Staff staff[MAX_STAFF];          // Array to store staff information

// Counters to track the total number of doctors, patients, and staff
int doctorCount = 0;   // Total number of doctors
int patientCount = 0;  // Total number of patients
int staffCount = 0;    // Total number of staff

// Function declarations
void showMenu();                      // Display the main menu
void addDoctor();                     // Add a new doctor to the system
void addPatient();                    // Add a new patient to the system
void generateReport();                // Generate a summary report
void saveData();                      // Save data to files
void loadData();                      // Load data from files
int readInteger();                    // Read a positive integer input
void sortDoctorsByName();             // Sort the list of doctors by their names
void sortPatientsByAge();             // Sort the list of patients by their ages
int calculateBill(Patient *patient);  // Calculate the bill for a patient
void clearInputBuffer();              // Clear the input buffer to prevent invalid input
void assignMedicationToPatient();     // Assign a medication to a patient
void viewDoctors();                   // Display the list of doctors
void viewPatients();                  // Display the list of patients
void scheduleAppointment();           // Schedule a new appointment
void viewAppointments();              // View all scheduled appointments
void addStaff();                      // Add a new staff member
void assignShiftToStaff();            // Assign a shift to a staff member
void viewStaffSchedules();            // View schedules of all staff members
void viewPatientBill();
void removePatient();  

// Main function to execute the hospital management system

/*
 * Main function to execute the hospital management system.
 * This function handles the overall operation of the system, which includes:
 * - Loading previously saved data into the system at the start (using loadData).
 * - Displaying the main menu continuously until the user chooses to exit.
 * - Allowing the user to select various options (e.g., add doctors, patients, view reports, etc.).
 * - Each option corresponds to a specific function such as adding a doctor, assigning medication to patients, scheduling appointments, generating reports, etc.
 * - The user's choice is processed using a switch-case statement, which calls the appropriate function based on the user's input.
 * - If the user selects the option to exit (choice 13), the program will print an exit message and terminate.
 * - Invalid choices are handled by displaying an error message.
 * 
 * The function also saves data to files (via the saveData function) to persist the information for later use.
 * This ensures that changes made during the program's execution are retained.
 */

int main() {
    // Load previously saved data into the system
    loadData();

    // Variable to store the user's menu choice
    int choice;

    // Main menu loop: continuously show the menu until the user exits
    while (1) {
        showMenu();  // Display the menu options
        printf("Enter your choice: ");
        choice = readInteger();  // Read the user's choice

        // Execute the selected operation
        switch (choice) {
            case 1:
                addDoctor();
                break;  // Add a new doctor
            case 2:
                addPatient();
                break;  // Add a new patient
            case 3:
                printf("Enter patient ID to assign medication: ");
                int patientIndex = readInteger();
                if (patientIndex >= 0 && patientIndex < patientCount) {
                    assignMedicationToPatient(patientIndex);  // Assign medication to the specified patient
                } else {
                    printf("Invalid patient ID.\n");
                }
                break;
            case 4:
                viewDoctors();  // View the list of doctors
                break;
            case 5:
                viewPatients();  // View the list of patients
                break;
            case 6:
                scheduleAppointment();  // Schedule a new appointment
                break;
            case 7:
                viewAppointments();  // View all scheduled appointments
                break;
            case 8:
                generateReport();  // Generate a report summary
                break;
            case 9:
                saveData();  // Save all data to files
                printf("Data saved successfully!\n");
                break;
            case 10:
                addStaff();  // Add a new staff member
                break;
            case 11:
                assignShiftToStaff();  // Assign a shift to a staff member
                break;
            case 12:
                viewStaffSchedules();  // View schedules of all staff
                break;
            case 13:
                removePatient();  // Call to the new function
                break;
            case 14:
                viewPatientBill();  // Call to the new function
                break;
            case 15:
                printf("Exiting program...\n");  // Exit the program
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");  // Handle invalid input
        }
    }

    return 0;
}

// Function to show the updated menu

/**
 * @brief Displays the main menu options to the user.
 * 
 * This function provides a list of available functionalities in the system, 
 * such as adding doctors, patients, assigning medications, managing appointments, etc. 
 * It serves as the main entry point for user interaction.
 */

void showMenu() {
    printf("\n----- Main Menu -----\n");
    printf("1. Add Doctor\n");
    printf("2. Add Patient\n");
    printf("3. Assign Medication to Patient\n");
    printf("4. View Doctors\n");
    printf("5. View Patients\n");
    printf("6. Schedule Appointment\n");
    printf("7. View Appointments\n");
    printf("8. Generate Report\n");
    printf("9. Save Data\n");
    printf("10. Add Staff\n");
    printf("11. Assign Shift to Staff\n");
    printf("12. View Staff Schedules\n");
    printf("13. Remove Patient\n");
    printf("14. View Patient's Bill\n");
    printf("15. Exit\n");
}

// Function to read an integer input

/**
 * @brief Reads a positive integer from the user input.
 * 
 * Ensures that the input is a valid positive integer by repeatedly prompting the user 
 * until a valid input is provided. Helps prevent invalid or negative inputs that could 
 * cause issues in other parts of the program.
 * 
 * @return A valid positive integer entered by the user.
 */

int readInteger() {
    int input;
    while (scanf("%d", &input) != 1 || input < 0) {
        clearInputBuffer(); 
        printf("Invalid input. Please enter a valid positive integer: ");
    }
    return input;
}

// Function to clear the input buffer

/**
 * @brief Clears the input buffer to handle stray characters.
 * 
 * Removes any remaining characters from the input buffer to prevent issues 
 * with subsequent user input. This function is especially useful after reading 
 * inputs where newline characters or invalid inputs might remain in the buffer.
 */

void clearInputBuffer() {
    while (getchar() != '\n');  // Clear the buffer
}

// Function to add a new doctor

/**
 * @brief Adds a new doctor to the system.
 * 
 * Prompts the user to enter details for a new doctor, including their name, age, 
 * specialty, and visiting fee. Ensures that the maximum doctor limit is not exceeded. 
 * Each doctor is stored in the `doctors` array.
 * 
 * - Name acts as a unique identifier.
 * - Validates that the maximum number of doctors has not been reached.
 */

void addDoctor() {
    if (doctorCount < MAX_DOCTORS) {
        printf("Enter doctor's name (this will be used as the ID): ");
        scanf("%s", doctors[doctorCount].name);  // Doctor's name is used as ID
        printf("Enter doctor's age: ");
        doctors[doctorCount].age = readInteger();
        printf("Enter doctor's specialty: ");
        scanf("%s", doctors[doctorCount].specialty);
        printf("Enter doctor's visiting fee: ");
        doctors[doctorCount].visitingFees = readInteger();

        doctorCount++;
        printf("Doctor added successfully!\n");
    } else {
        printf("Maximum doctor limit reached.\n");
    }
}

// Function to add a new patient

/**
 * @brief Adds a new patient to the system.
 * 
 * This function collects details about the patient, such as name, age, 
 * diagnosis, and room number. It also links the patient to a specific doctor 
 * by matching the doctor’s name. Validates input and ensures that the maximum 
 * patient limit is not exceeded.
 * 
 * - Links the patient to a doctor using the doctor's name as an identifier.
 * - Checks if the entered doctor exists in the system.
 */

void addPatient() {
    if (patientCount < MAX_PATIENTS) {
        printf("Enter patient's name: ");
        scanf("%s", patients[patientCount].name);
        printf("Enter patient's age: ");
        patients[patientCount].age = readInteger();
        printf("Enter patient's diagnosis: ");
        scanf("%s", patients[patientCount].diagnosis);
        printf("Enter patient's room number: ");
        patients[patientCount].roomNumber = readInteger();

        // Ask for the doctor's name and assign the doctor ID based on the name
        printf("Enter the doctor's name (used as doctor ID): ");
        char doctorName[100];
        scanf("%s", doctorName);

        // Find the doctor with the matching name and assign to the patient
        int doctorFound = 0;
        for (int i = 0; i < doctorCount; i++) {
            if (strcmp(doctors[i].name, doctorName) == 0) {
                patients[patientCount].doctorID = i;  // Assign the doctor by index
                doctorFound = 1;
                break;
            }
        }

        if (!doctorFound) {
            printf("Doctor not found.\n");
            return;
        }

        patientCount++;
        printf("Patient added successfully!\n");
    } else {
        printf("Maximum patient limit reached.\n");
    }
}

// Function to sort doctors by name

/**
 * @brief Sorts the list of doctors alphabetically by their names.
 * 
 * Uses a simple bubble sort algorithm to sort the `doctors` array based 
 * on the `name` field. Sorting helps in organizing the data for better 
 * readability or searching.
 */

void sortDoctorsByName() {
    Doctor temp;
    for (int i = 0; i < doctorCount - 1; i++) {
        for (int j = i + 1; j < doctorCount; j++) {
            if (strcmp(doctors[i].name, doctors[j].name) > 0) {
                temp = doctors[i];
                doctors[i] = doctors[j];
                doctors[j] = temp;
            }
        }
    }
    printf("Doctors sorted by name.\n");
}

// Function to sort patients by age

/**
 * @brief Sorts the list of patients in ascending order of their ages.
 * 
 * Uses a bubble sort algorithm to sort the `patients` array based 
 * on the `age` field. This is useful for generating reports or 
 * prioritizing patients by age.
 */

void sortPatientsByAge() {
    Patient temp;
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = i + 1; j < patientCount; j++) {
            if (patients[i].age > patients[j].age) {
                temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
    printf("Patients sorted by age.\n");
}

// Function to save the current data of doctors, patients, and staff into respective files.

/*
 * Function to save the current data of doctors, patients, and staff into respective files.
 * This function writes the data of all doctors, patients, and staff to their corresponding files in binary mode.
 * It first writes the count of each category (doctors, patients, and staff) and then their respective data.
 * If the files are successfully opened, the data is saved; otherwise, an error message is displayed.
 */

void saveData() {
    // Open the files for writing in binary mode
    FILE *doctorFile = fopen("doctors.dat", "wb");
    FILE *patientFile = fopen("patients.dat", "wb");
    FILE *staffFile = fopen("staff.dat", "wb");  // New staff data file

    // Check if all files are opened successfully
    if (doctorFile && patientFile && staffFile) {
        // Save the number of doctors followed by the data of each doctor
        fwrite(&doctorCount, sizeof(int), 1, doctorFile);
        fwrite(doctors, sizeof(Doctor), doctorCount, doctorFile);

        // Save the number of patients followed by the data of each patient
        fwrite(&patientCount, sizeof(int), 1, patientFile);
        fwrite(patients, sizeof(Patient), patientCount, patientFile);

        // Save the number of staff followed by the data of each staff member
        fwrite(&staffCount, sizeof(int), 1, staffFile);
        fwrite(staff, sizeof(Staff), staffCount, staffFile);

        // Close the files after writing the data
        fclose(doctorFile);
        fclose(patientFile);
        fclose(staffFile);
    } else {
        // Error handling if files can't be opened
        printf("Error saving data.\n");
    }
}

// Function to load previously saved data for doctors, patients, and staff from files.

/*
 * Function to load previously saved data for doctors, patients, and staff from files.
 * This function opens the corresponding files in binary mode and reads the data into the memory.
 * It reads the count of doctors, patients, and staff, followed by the actual data of each.
 * If the files don't exist or can't be opened, a message is displayed indicating no saved data.
 */

void loadData() {
    // Open the files for reading in binary mode
    FILE *doctorFile = fopen("doctors.dat", "rb");
    FILE *patientFile = fopen("patients.dat", "rb");
    FILE *staffFile = fopen("staff.dat", "rb");  // New staff data file

    // Check if all files exist and can be read
    if (doctorFile && patientFile && staffFile) {
        // Read the number of doctors and their data from the file
        fread(&doctorCount, sizeof(int), 1, doctorFile);
        fread(doctors, sizeof(Doctor), doctorCount, doctorFile);

        // Read the number of patients and their data from the file
        fread(&patientCount, sizeof(int), 1, patientFile);
        fread(patients, sizeof(Patient), patientCount, patientFile);

        // Read the number of staff and their data from the file
        fread(&staffCount, sizeof(int), 1, staffFile);
        fread(staff, sizeof(Staff), staffCount, staffFile);

        // Close the files after reading
        fclose(doctorFile);
        fclose(patientFile);
        fclose(staffFile);
    } else {
        // If files don't exist, print a message and start fresh
        printf("No saved data found, starting fresh.\n");
    }
}

// Function to generate a detailed report of staff members and their schedules.

/*
 * Function to generate a detailed report of staff members and their schedules.
 * This function iterates over all staff members and generates a report that includes:
 * - Staff member's name, role, and contact information
 * - The shifts assigned to each staff member
 * - A summary of the total shifts assigned across all staff
 * - A breakdown of shifts per day of the week
 * It also includes details of staff members who have no shifts assigned.
 */

void generateReport() {
    // If no staff members are available, print a message and return
    if (staffCount == 0) {
        printf("No staff members available to generate a report.\n");
        return;
    }

    // Print header for the staff report
    printf("\n--- Staff Schedule Report ---\n");
    printf("Total number of staff: %d\n", staffCount);
    
    int totalShifts = 0;
    int staffWithNoShifts = 0;

    // Loop through all staff members to display their details
    for (int i = 0; i < staffCount; i++) {
        printf("\nStaff Member: %s\n", staff[i].name);
        printf("Role: %s\n", staff[i].role);
        printf("Contact Info: %s\n", staff[i].contactInfo);

        // Count total shifts assigned across all staff members
        totalShifts += staff[i].shiftCount;

        // If the staff member has no shifts, note it and print a message
        if (staff[i].shiftCount == 0) {
            staffWithNoShifts++;
            printf("No shifts assigned.\n");
        } else {
            // Print each shift assigned to the staff member
            printf("Assigned Shifts:\n");
            for (int j = 0; j < staff[i].shiftCount; j++) {
                printf("  Day: %s, Shift: %s to %s, Role: %s\n", 
                    staff[i].schedule[j].day, 
                    staff[i].schedule[j].startTime, 
                    staff[i].schedule[j].endTime, 
                    staff[i].schedule[j].role);
            }
        }
    }

    // Print summary of shifts and staff members with no shifts
    printf("\n--- Report Summary ---\n");
    printf("Total number of shifts assigned across all staff: %d\n", totalShifts);
    printf("Staff members with no shifts: %d\n", staffWithNoShifts);

    // Count shifts for each day of the week (Sunday-Saturday)
    printf("\n--- Shifts Summary by Day ---\n");
    int shiftsPerDay[7] = {0};  // Array for counting shifts per day (7 days a week)

    // Loop through all staff and their shifts to count shifts for each day
    for (int i = 0; i < staffCount; i++) {
        for (int j = 0; j < staff[i].shiftCount; j++) {
            if (strcmp(staff[i].schedule[j].day, "Sunday") == 0) {
                shiftsPerDay[0]++;
            } else if (strcmp(staff[i].schedule[j].day, "Monday") == 0) {
                shiftsPerDay[1]++;
            } else if (strcmp(staff[i].schedule[j].day, "Tuesday") == 0) {
                shiftsPerDay[2]++;
            } else if (strcmp(staff[i].schedule[j].day, "Wednesday") == 0) {
                shiftsPerDay[3]++;
            } else if (strcmp(staff[i].schedule[j].day, "Thursday") == 0) {
                shiftsPerDay[4]++;
            } else if (strcmp(staff[i].schedule[j].day, "Friday") == 0) {
                shiftsPerDay[5]++;
            } else if (strcmp(staff[i].schedule[j].day, "Saturday") == 0) {
                shiftsPerDay[6]++;
            }
        }
    }

    // Print the number of shifts assigned per day
    const char *daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for (int i = 0; i < 7; i++) {
        printf("%s: %d shifts\n", daysOfWeek[i], shiftsPerDay[i]);
    }

    // End of report
    printf("\n--- End of Report ---\n");
}

// Function to calculate patient's bill based on room and doctor's fees.

/*
 * Function to calculate the total bill for a patient based on room charge and doctor's fee.
 * This function calculates the total bill by adding the fixed room charge to the doctor's fee for the patient.
 * The room charge is predefined (in this case, $100), and the doctor's fee is fetched from the doctor's data.
 * The function returns the sum as the patient's total bill.
 */

int calculateBill(Patient *patient) {
    int roomCharge = 100;  // Example room charge
    int doctorFee = doctors[patient->doctorID].visitingFees;

    return roomCharge + doctorFee;
}

// Function to assign medications to a patient

/*
 * Function to assign medication to a patient by updating their medication list.
 * This function allows the assignment of a medication to a patient if they haven't reached the maximum medication limit.
 * The user is prompted to enter the medication name and dosage, which is then added to the patient's medication list.
 * If the patient has already reached the maximum allowed medications, an error message is displayed.
 */

void assignMedicationToPatient(int patientIndex) {
    if (patients[patientIndex].medicationCount < MAX_MEDICATIONS) {
        printf("Enter medication name: ");
        scanf("%s", patients[patientIndex].medications[patients[patientIndex].medicationCount].name);
        printf("Enter medication dosage: ");
        scanf("%s", patients[patientIndex].medications[patients[patientIndex].medicationCount].dosage);

        patients[patientIndex].medicationCount++;
        printf("Medication assigned successfully!\n");
    } else {
        printf("This patient has reached the maximum number of medications.\n");
    }
}

// Function to view all doctors

/*
 * Function to display a list of all patients, their details, and assigned medications.
 * This function iterates over all patients, printing their personal details like name, age, and doctor assigned to them.
 * It also lists medications that are assigned to each patient, if any.
 * If no patients are available, a message is displayed indicating no data is available.
 */

void viewDoctors() {
    if (doctorCount == 0) {
        printf("No doctors available.\n");
        return;
    }

    printf("\n----- Doctors List -----\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("Doctor #%d\n", i + 1);
        printf("Name: %s\n", doctors[i].name);
        printf("Age: %d\n", doctors[i].age);
        printf("Specialty: %s\n", doctors[i].specialty);
        printf("Visiting Fee: %d\n\n", doctors[i].visitingFees);
    }
}

// Function to view all patients

/*
 * Function to view a list of all patients along with their personal and medical details.
 * This function iterates through the list of patients and displays:
 * - Patient's name, age, diagnosis, and room number
 * - Assigned doctor's name
 * - List of medications assigned to the patient, if any
 * If no patients are available, a message is displayed indicating the absence of patients.
 */

void viewPatients() {
    if (patientCount == 0) {
        printf("No patients available.\n");
        return;
    }

    printf("\n----- Patients List -----\n");
    for (int i = 0; i < patientCount; i++) {
        printf("Patient #%d\n", i + 1);
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Diagnosis: %s\n", patients[i].diagnosis);
        printf("Room Number: %d\n", patients[i].roomNumber);
        printf("Assigned Doctor: %s\n", doctors[patients[i].doctorID].name);  // Show doctor's name

        // Display medications
        if (patients[i].medicationCount > 0) {
            printf("Medications:\n");
            for (int j = 0; j < patients[i].medicationCount; j++) {
                printf("  %s, Dosage: %s\n", patients[i].medications[j].name, patients[i].medications[j].dosage);
            }
        } else {
            printf("No medications assigned.\n");
        }
    }
}

// Function to schedule an appointment

/*
 * Function to schedule a new appointment between a patient and a doctor.
 * This function performs the following steps:
 * - Requests a valid patient ID and checks if the patient exists
 * - Requests a valid doctor ID and checks if the doctor exists
 * - Takes the appointment date as input from the user
 * - Stores the appointment information in the appointments list
 * - If the maximum appointment limit is reached, an error message is displayed
 */

void scheduleAppointment() {
    if (appointmentCount < MAX_APPOINTMENTS) {
        int patientID, doctorID;
        char appointmentDate[20];

        // Get the patient ID and validate it
        printf("Enter patient ID (0-%d): ", patientCount - 1);
        patientID = readInteger();
        if (patientID < 0 || patientID >= patientCount) {
            printf("Invalid patient ID.\n");
            return;
        }

        // Get the doctor ID and validate it
        printf("Enter doctor ID (0-%d): ", doctorCount - 1);
        doctorID = readInteger();
        if (doctorID < 0 || doctorID >= doctorCount) {
            printf("Invalid doctor ID.\n");
            return;
        }

        // Get the appointment date
        printf("Enter appointment date (YYYY-MM-DD): ");
        scanf("%s", appointmentDate);

        // Store the appointment
        appointments[appointmentCount].patientID = patientID;
        appointments[appointmentCount].doctorID = doctorID;
        strcpy(appointments[appointmentCount].appointmentDate, appointmentDate);

        // Increment the appointment count
        appointmentCount++;
        printf("Appointment scheduled successfully!\n");
    } else {
        printf("Maximum appointment limit reached.\n");
    }
}

// Function to view all appointments

/*
 * Function to view a list of all scheduled appointments.
 * This function iterates through all scheduled appointments and displays:
 * - Patient's name
 * - Doctor's name
 * - Appointment date
 * If no appointments are scheduled, it will print a message indicating so.
 * It also validates the patient and doctor data before displaying the appointment information.
 */

void viewAppointments() {
    if (appointmentCount == 0) {
        printf("No appointments scheduled.\n");
        return;
    }

    printf("\n----- Appointments List -----\n");
    for (int i = 0; i < appointmentCount; i++) {
        int patientID = appointments[i].patientID;
        int doctorID = appointments[i].doctorID;

        // Validate the patient and doctor ID before displaying
        if (patientID >= 0 && patientID < patientCount && doctorID >= 0 && doctorID < doctorCount) {
            printf("Appointment #%d\n", i + 1);
            printf("Patient: %s\n", patients[patientID].name);
            printf("Doctor: %s\n", doctors[doctorID].name);
            printf("Date: %s\n\n", appointments[i].appointmentDate);
        } else {
            printf("Error: Invalid patient or doctor data for appointment #%d\n", i + 1);
        }
    }
}

// Function to view the current bill of a patient

/*
 * Function to view and calculate the total bill of a specific patient.
 * This function performs the following steps:
 * - Requests the patient ID and validates it
 * - Calculates the patient's total bill by adding the room charge and doctor's fee
 * - Displays the patient's name, room charge, doctor's fee, and the total bill amount
 * If an invalid patient ID is entered, an error message is displayed.
 */

void viewPatientBill() {
    printf("Enter patient ID to view the bill: ");
    int patientIndex = readInteger();

    if (patientIndex >= 0 && patientIndex < patientCount) {
        // Calculate the bill for the patient
        int bill = calculateBill(&patients[patientIndex]);

        // Display the calculated bill
        printf("Patient: %s\n", patients[patientIndex].name);
        printf("Room Charge: 100\n");  // Example room charge
        printf("Doctor's Fee: %d\n", doctors[patients[patientIndex].doctorID].visitingFees);
        printf("Total Bill: %d\n", bill);
    } else {
        printf("Invalid patient ID.\n");
    }
}

// Function to add a new staff member

/*
 * Function to add a new staff member to the system.
 * This function prompts the user for the staff member's:
 * - Name
 * - Role (e.g., Nurse, Admin, etc.)
 * - Contact information
 * It then initializes the shift count to 0 and adds the staff member to the staff list.
 * If the maximum staff limit has been reached, an error message is displayed.
 */

void addStaff() {
    if (staffCount < MAX_STAFF) {
        printf("Enter staff member's name: ");
        scanf("%s", staff[staffCount].name);
        printf("Enter staff member's role (e.g., Nurse, Admin): ");
        scanf("%s", staff[staffCount].role);
        printf("Enter staff member's contact info: ");
        scanf("%s", staff[staffCount].contactInfo);
        
        staff[staffCount].shiftCount = 0;  // Initialize shift count
        staffCount++;
        printf("Staff member added successfully!\n");
    } else {
        printf("Maximum staff limit reached.\n");
    }
}


// Function to assign shift to a staff member

/*
 * Function to assign a shift to a specific staff member.
 * This function performs the following steps:
 * - Requests the name of the staff member and searches for it in the staff list
 * - If found, it prompts for the details of the shift: day, start time, end time, and role
 * - It then assigns the shift to the staff member and increments their shift count
 * If the staff member is not found, an error message is displayed.
 */

void assignShiftToStaff() {
    char name[100];
    printf("Enter the staff member's name to assign shift: ");
    scanf("%s", name);

    int staffIndex = -1;
    for (int i = 0; i < staffCount; i++) {
        if (strcmp(staff[i].name, name) == 0) {
            staffIndex = i;
            break;
        }
    }

    if (staffIndex == -1) {
        printf("Staff member not found.\n");
        return;
    }

    Shift shift;
    printf("Enter day for the shift: ");
    scanf("%s", shift.day);
    printf("Enter start time for the shift: ");
    scanf("%s", shift.startTime);
    printf("Enter end time for the shift: ");
    scanf("%s", shift.endTime);
    printf("Enter role for the shift: ");
    scanf("%s", shift.role);

    staff[staffIndex].schedule[staff[staffIndex].shiftCount] = shift;
    staff[staffIndex].shiftCount++;
    printf("Shift assigned successfully to %s!\n", staff[staffIndex].name);
}


// Function to view all staff schedules

/*
 * Function to view the schedules of all staff members.
 * This function iterates through all staff members and displays:
 * - Staff member's name and role
 * - Contact information
 * - The shifts assigned to the staff member (day, start time, end time, and role)
 * If no shifts are assigned to a staff member, it will print a message indicating that.
 * If no staff members are available, a message is displayed.
 */

void viewStaffSchedules() {
    if (staffCount == 0) {
        printf("No staff members found.\n");
        return;
    }

    for (int i = 0; i < staffCount; i++) {
        printf("\nStaff Member: %s (%s)\n", staff[i].name, staff[i].role);
        printf("Contact Info: %s\n", staff[i].contactInfo);
        printf("Assigned Shifts:\n");

        // Check if the staff member has any assigned shifts
        if (staff[i].shiftCount == 0) {
            printf("  No shifts assigned.\n");
        } else {
            for (int j = 0; j < staff[i].shiftCount; j++) {
                printf("  Day: %s, Shift: %s to %s, Role: %s\n", 
                    staff[i].schedule[j].day, 
                    staff[i].schedule[j].startTime, 
                    staff[i].schedule[j].endTime, 
                    staff[i].schedule[j].role);
            }
        }
    }
}

// Function to remove a patient and display their bill before removal

/*
 * Function to remove a patient from the system.
 * This function performs the following:
 * - Prompts the user for the patient ID to remove
 * - Displays the patient's bill before removal
 * - Removes the patient from the list by shifting subsequent entries
 * - Decrements the patient count to reflect the removal
 * If the patient ID is invalid, an error message is displayed.
 */

void removePatient() {
    printf("Enter the patient ID to remove: ");
    int patientID = readInteger();

    if (patientID >= 0 && patientID < patientCount) {
        // Display the bill for the patient
        int bill = calculateBill(&patients[patientID]);
        printf("Patient: %s\n", patients[patientID].name);
        printf("Room Charge: 100\n");  // Example room charge
        printf("Doctor's Fee: %d\n", doctors[patients[patientID].doctorID].visitingFees);
        printf("Total Bill: %d\n", bill);

        // Remove the patient by shifting subsequent entries
        for (int i = patientID; i < patientCount - 1; i++) {
            patients[i] = patients[i + 1];
        }
        patientCount--;

        printf("Patient removed successfully!\n");
    } else {
        printf("Invalid patient ID.\n");
    }
}
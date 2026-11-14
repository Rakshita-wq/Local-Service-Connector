

void insertProviderAtFront(Provider* newProvider)
{
    newProvider->setNext(providerHead);
    providerHead = newProvider;
}

bool providerPhoneExists(string phone)
{
    Provider* current = providerHead;

    while (current != NULL)
    {
        if (current->getPhone() == phone)
            return true;

        current = current->getNext();
    }

    return false;
}

void signUpProvider()
{
    cout << "\n========== SIGN UP AS PROVIDER ==========\n";

    string name, phone, password, service, area;
    string bestFriend, email;

    cout << "Enter provider name: ";
    getline(cin, name);

    while (true)
    {
        cout << "Enter phone number: ";
        getline(cin, phone);

        if (!providerPhoneExists(phone))
            break;

        cout << "Phone number already registered.\n";
    }

    cout << "Enter password: ";
    getline(cin, password);

    service = chooseService();
    area = User::chooseArea();

    cout << "Enter best friend name: ";
    getline(cin, bestFriend);

    cout << "Enter personal email: ";
    getline(cin, email);

    globalID++;

    Provider* newProvider = new Provider(
        globalID, name, phone, password,
        service, area, bestFriend, email
    );

    insertProviderAtFront(newProvider);

    cout << "\nProvider account created successfully.\n";
    cout << "Your unique ID is: " << globalID << "\n";
}

Provider* findProviderByIdentifier(string identifier)
{
    Provider* current = providerHead;

    while (current != NULL)
    {
        if (identifier == to_string(current->getID()) ||
            identifier == current->getPhone())
        {
            return current;
        }

        current = current->getNext();
    }

    return NULL;
}

void forgotProviderPassword(Provider* provider)
{
    string friendName, email, newPassword;

    cout << "\n========== PASSWORD RECOVERY ==========\n";

    cout << "Enter best friend name: ";
    getline(cin, friendName);

    cout << "Enter personal email: ";
    getline(cin, email);

    if (provider->verifySecurityAnswers(friendName, email))
    {
        cout << "Answers matched.\n";

        cout << "Enter new password: ";
        getline(cin, newPassword);

        provider->setPassword(newPassword);

        cout << "Password reset successfully.\n";
    }
    else
    {
        cout << "Security answers did not match.\n";
    }
}

void providerChangeDetailMenu(Provider* provider)
{
    while (true)
    {
        cout << "\n========== CHANGE DETAIL ==========\n";
        cout << "1. Change Name\n";
        cout << "2. Change Phone Number\n";
        cout << "3. Change Service\n";
        cout << "4. Change Password\n";
        cout << "5. Change Area\n";
        cout << "6. Change Security Answers\n";
        cout << "7. Back\n";

        int choice = getInteger("Enter choice: ");

        switch (choice)
        {
        case 1:
            provider->changeName();
            break;

        case 2:
            provider->changePhone();
            break;

        case 3:
            provider->changeService();
            break;

        case 4:
            provider->changePassword();
            break;

        case 5:
            provider->changeArea();
            break;

        case 6:
            provider->changeSecurityAnswers();
            break;

        case 7:
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}

void providerMenu(Provider* currentProvider)
{
    while (true)
    {
        cout << "\n========== PROVIDER DASHBOARD ==========\n";
        cout << "Welcome, " << currentProvider->getName() << "\n";
        cout << "1. Show Detail\n";
        cout << "2. Change Detail\n";
        cout << "3. Service Requests\n";
        cout << "4. Completed Bookings\n";
        cout << "5. Logout\n";

        int choice = getInteger("Enter choice: ");

        switch (choice)
        {
        case 1:
            currentProvider->showDetail();
            break;

        case 2:
            providerChangeDetailMenu(currentProvider);
            break;

        case 3:
            currentProvider->serviceRequestMenu();
            break;

        case 4:
            currentProvider->completedBookings.display(
                "RECENT COMPLETED BOOKINGS"
            );
            break;

        case 5:
            cout << "Logged out successfully.\n";
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}

void signInProvider()
{
    cout << "\n========== SIGN IN AS PROVIDER ==========\n";
    cout << "You may use ID or phone number.\n";

    string identifier;

    cout << "Enter ID/phone number: ";
    getline(cin, identifier);

    Provider* provider = findProviderByIdentifier(identifier);

    if (provider == NULL)
    {
        cout << "No provider found.\n";
        return;
    }

    while (true)
    {
        string password;

        cout << "Enter password: ";
        getline(cin, password);

        if (provider->verifyPassword(password))
        {
            cout << "Login successful.\n";
            providerMenu(provider);
            return;
        }

        cout << "\nWrong password.\n";
        cout << "1. Retry password\n";
        cout << "2. Forgot password\n";
        cout << "3. Back\n";

        int choice = getInteger("Enter choice: ");

        if (choice == 2)
            forgotProviderPassword(provider);

        else if (choice == 3)
            return;
    }
}
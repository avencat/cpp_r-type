# Server Configuration class
## 1. Attributes
### 1.1. silent
**Type:**  
`bool`

**Getter/Setter:**  
Both.

**Description:**  
This attribute, when set to true, will print the configuration when checks and update are performed.

### 1.2. config
**Type:**  
`std::map<std::string, std::string>`

**Getter/Setter:**  
None. Use *readUpdateConfig* to update the config map with last config file used or *setConfigKey* to update/set a key.

**Description:**  
This attribute contains all the config options and their values. All keys (options) are stored in lowercase.  
The config values can be retrieved using *getConfigKey*.

**Default values:**  
- port: 4242
- maxclients: 10
- database: spider.db

### 1.3. whitelist
**Type:**  
`std::vector<std::string>`

**Getter/Setter:**  
None. Use *readUpdateWhitelist* to update the whitelist using the *"whitelist"* key in config or *addToWhitelist/removeFromWhitelist*.

**Description:**  
This attribute contains every authorized address. If no whitelist key exists in config, every ip is considered as valid unless present in blacklist.

### 1.4. blacklist
**Type:**  
`std::vector<std::string>`

**Getter/Setter:**  
None. Use *readUpdateBlacklist* to update the blacklist using the *"blacklist"* key in config or *addToBlacklist/removeFromBlacklist*.

**Description:**  
This attribute contains every authorized address. If no blacklist key exists in config, every ip is considered as valid unless a whitelist file exists and does not contain it.

## 2. Methods
### 2.1. Constructor/Destructor
#### 2.1.1. Constructor
**Prototype:**  
```c++
Configuration(const std::string &path, const bool _silent = true);
```
[///]: <> (_Removing atom color bug_)
**Description:**  
Upon creation, the Configuration class will set default values and try to read the given path to config file in order to call the *readUpdateConfig* method.

**Example:**  
```c++
Configuration cfg("example.ini", true);
```

#### 2.1.2. Destructor
**Prototype:**  
```c++
~Configuration();
```

**Description:**  
Nothing.

### 2.2. Configuration setting
#### 2.2.1. readUpdateConfig
**Prototype:**  
```c++
void readUpdateConfig();
```

**Description:**  
The *readUpdateConfig* method will read all keys stored in the configuration file given upon creation or update and store them in the config map.

**Example:**  
example.cpp:
```c++
Configuration cfg("example.ini");

cfg.readUpdateConfig(); // This call is optional as it is performed during class creation.
```
example.ini:
```Ini
port=4221
whitelist=./lists/whitelist
blacklist=./lists/blacklist
```

#### 2.2.2. readUpdateWhitelist
**Prototype:**  
```c++
void readUpdateWhitelist();
```

**Description:**  
The *readUpdateWhitelist* method will read the whitelist file, if its path is present in the config map, and **add** any line in it to the whitelist vector.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.readUpdateWhitelist(); // This call is optional as it is performed during class creation.
```

#### 2.2.3. readUpdateBlacklist
**Prototype:**  
```c++
void readUpdateBlacklist();
```

**Description:**  
The *readUpdateBlacklist* method will read the blacklist file, if its path is present in the config map, and **add** any line in it to the blacklist vector.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.readUpdateBlacklist(); // This call is optional as it is performed during class creation.
```

#### 2.2.4. addToWhitelist
**Prototype:**  
```c++
void addToWhitelist(const std::string &ip);
```

**Description:**  
The *addToWhitelist* method will add the given ip to the whitelist vector.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.addToWhitelist("192.168.1.2");
cfg.addToWhitelist("192.168.1.3:4242");
```

#### 2.2.5. addToBlacklist
**Prototype:**  
```c++
void addToBlacklist(const std::string &ip);
```

**Description:**  
The *addToBlacklist* method will add the given ip to the blacklist vector.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.addToBlacklist("192.168.1.2");
cfg.addToBlacklist("192.168.1.3:4242");
```

#### 2.2.6. removeFromWhitelist
**Prototype:**  
```c++
void removeFromWhitelist(const std::string &ip);
```

**Description:**  
The *removeFromWhitelist* method will remove the given ip from the whitelist vector.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.removeFromWhitelist("192.168.1.2");
cfg.removeFromWhitelist("192.168.1.3:4242");
```

#### 2.2.7. removeFromBlacklist
**Prototype:**  
```c++
void removeFromBlacklist(const std::string &ip);
```

**Description:**  
The *removeFromBlacklist* method will remove the given ip from the blacklist vector.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.removeFromBlacklist("192.168.1.2");
cfg.removeFromBlacklist("192.168.1.3:4242");
```

### 2.3. Infos checkers/printers
#### 2.3.1. isAuthorizedIP
**Prototype:**  
```c++
bool	isAuthorizedIP(const std::string &ip, const unsigned short port) const;
```

**Description:**  
The *isAuthorizedIP* method will return true if no (black/white)list exists or if both of theses list authorize the given address/port combination.

**Example:**  
```c++
Configuration cfg("example.ini");

if (cfg.isAuthorizedIP("192.168.1.2"))
  std::cout << "IP is authorized" << std::endl;
if (cfg.isAuthorizedIP("192.168.1.3:4242"))
  std::cout << "IP is authorized" << std::endl;
```

#### 2.3.2. isAuthorizedWhite
**Prototype:**  
```c++
bool	isAuthorizedWhite(const std::string &ip, const unsigned short port) const;
```

**Description:**  
The *isAuthorizedWhite* method will return true if no whitelist exists or if the list authorize the given address/port combination.

**Example:**  
```c++
Configuration cfg("example.ini");

if (cfg.isAuthorizedWhite("192.168.1.2"))
  std::cout << "IP is authorized" << std::endl;
if (cfg.isAuthorizedWhite("192.168.1.3:4242"))
  std::cout << "IP is authorized" << std::endl;
```

#### 2.3.3. isAuthorizedBlack
**Prototype:**  
```c++
bool	isAuthorizedBlack(const std::string &ip, const unsigned short port) const;
```

**Description:**  
The *isAuthorizedBlack* method will return true if no blacklist exists or if the list authorize the given address/port combination.

**Example:**  
```c++
Configuration cfg("example.ini");

if (cfg.isAuthorizedBlack("192.168.1.2"))
  std::cout << "IP is authorized" << std::endl;
if (cfg.isAuthorizedBlack("192.168.1.3:4242"))
  std::cout << "IP is authorized" << std::endl;
```

#### 2.3.4. printConfig
**Prototype:**  
```c++
void  printConfig();
```

**Description:**  
The *printConfig* method will print the whole config map in the form "Key=Value".

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.printConfig();
```

#### 2.3.5. printWhitelist
**Prototype:**  
```c++
void  printWhitelist();
```

**Description:**  
The *printWhitelist* method will print the whole whitelist.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.printWhitelist();
```

#### 2.3.6. printBlacklist
**Prototype:**  
```c++
void  printBlacklist();
```

**Description:**  
The *printBlacklist* method will print the whole blacklist.

**Example:**  
```c++
Configuration cfg("example.ini");

cfg.printBlacklist();
```

#3. Class requirement
#3.1. Makefile
Since c++11 methods are used within the class code, compiler should use `--std=c++11` at least in order to compile the Configuration class.

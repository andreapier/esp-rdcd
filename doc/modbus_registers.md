| Setting                               | Address     | Remarks
|---------------------------------------|-------------|--------|
| Set unoccupied air flow               | 1511 & 1513 |
| Set economy air flow                  | 1507 & 1509 |
| Set comfort air flow                  | 1503 & 1505 |  
| Set State                             | 2001        | 1: protection (stopped, only if enabled by installer); 2: unoccupied; 3: economy; 4: comfort
| Operating time for filter replacement | 1623        | Installer sets the time until the filter needs to be replaced. After this time, the user should get a notification
| Operating time filter                 | 1621        | How many hours since last filter replacement. If this value exceeds the value set in register 1623 (set by installer), a B-alarm is trigger
| General Alarm                         | 4012        | (B-alarm), 4010 (A-alarm)
| General Alarm RESET/ACK               | 3003, 3004  |
| By-pass on/off                        | 2028        | 0: closed (full heat recovery); 1: open (heat recovery bypassed)
| Outside air temperature               | 501         |
| Supply air temperature                | 505         |
| Extract air temperature               | 509         |
| Exhaust air temperature               | 513         |

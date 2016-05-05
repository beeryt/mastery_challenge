## The while loop
### The basics
```C
while (condition) {
  // code
}
```
---
## The for loop
### Do something n times
#### Using a while loop
```C
int i = 0;
while (i < n) {
  // code
  i++;
}
```
#### Using a for loop
```C
for (int i = 0; i < n; i++) {
  // code
}
```
#### A for loop as a while loop
```C
for (;condition;) {
  // code
}
```
---
## The do-while loop
### Do something, then do it while condition is true
#### Using a while loop
```C
// code
while (condition) {
  // code
}
```
#### We can do better!
```C
do {
  // code
} while (condition);
```
---
## The infinite loop
### Sometimes we want this:
```C
while (true) {
  // code
}
```
### Sometimes we don't
```C
for (int i = 0; i < n; i++) {
  if (condition)
    i--;  // This could cause an infinite loop!!!
}
```
---

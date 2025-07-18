
# copy.c 와 fcopy.c 분석

## 개요

`copy.c`와 `fcopy.c`는 모두 파일을 복사하는 C 프로그램입니다. 
두 파일의 주된 차이점은 `copy.c`는 시스템 콜(system call)을 사용하는 저수준(low-level) 파일 입출력을 사용하고, `fcopy.c`는 표준 입출력 라이브러리(standard I/O library)를 사용한다는 점입니다.

## copy.c

### 코드 설명

`copy.c`는 `open`, `read`, `write`, `close`와 같은 시스템 콜을 직접 사용하여 파일을 복사합니다.

- **`open`**: 파일을 열 때 사용하며, 읽기 전용(`O_RDONLY`) 또는 쓰기 전용(`O_WRONLY`), 파일이 없을 경우 생성(`O_CREAT`), 파일이 존재할 경우 내용 삭제(`O_TRUNC`) 등의 옵션을 지정할 수 있습니다.
- **`read`**: 파일 디스크립터(`in`)로부터 데이터를 읽어 버퍼(`buf`)에 저장합니다.
- **`write`**: 버퍼(`buf`)의 내용을 파일 디스크립터(`out`)에 씁니다.
- **`close`**: 사용이 끝난 파일 디스크립터를 닫습니다.

### 사용법

```bash
gcc copy.c -o copy
./copy <원본 파일> <대상 파일>
```

## fcopy.c

### 코드 설명

`fcopy.c`는 `fopen`, `fread`, `fwrite`, `fclose`와 같은 표준 입출력 라이브러리 함수를 사용하여 파일을 복사합니다.

- **`fopen`**: 파일을 열 때 사용하며, "r"(읽기), "w"(쓰기) 등의 모드를 지정합니다.
- **`fread`**: 파일 포인터(`in`)가 가리키는 파일로부터 데이터를 읽어 버퍼(`buf`)에 저장합니다.
- **`fwrite`**: 버퍼(`buf`)의 내용을 파일 포인터(`out`)가 가리키는 파일에 씁니다.
- **`fclose`**: 사용이 끝난 파일 포인터를 닫습니다.

### 사용법

```bash
gcc fcopy.c -o fcopy
./fcopy <원본 파일> <대상 파일>
```

## 주요 차이점

| 구분 | copy.c (시스템 콜) | fcopy.c (표준 입출력 라이브러리) |
|---|---|---|
| **입출력 방식** | 저수준 파일 입출력 | 고수준 파일 입출력 |
| **사용 함수** | `open`, `read`, `write`, `close` | `fopen`, `fread`, `fwrite`, `fclose` |
| **버퍼링** | 직접 버퍼(char buf[BUFSIZ])를 선언하여 사용 | 내부적으로 버퍼링을 수행하여 성능 향상 |
| **이식성** | 주로 유닉스 계열 시스템에서 사용 | 다양한 운영체제에서 높은 이식성 제공 |
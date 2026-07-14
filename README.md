# JSON CRUD Console Application

JSON 파일을 데이터 저장소로 사용하는 C++ CRUD 콘솔 애플리케이션입니다.
JSON 파싱/저장 로직을 외부 라이브러리 없이 직접 PoC로 구현해 먼저 익힌 뒤,
그 코드 구조를 그대로 유지하며 CRUD 기능을 확장하는 학습 프로젝트입니다.

## 기술 스택
- C++20 (MSVC, PlatformToolset v145)
- JSON 파싱/직렬화: 외부 라이브러리 없이 직접 구현
- [GoogleTest](https://github.com/google/googletest) (gmock 포함, NuGet 설치)

## 개발 방식
이 프로젝트는 SDD + TDD로 개발합니다. 기능마다 `docs/specs/`에
스펙을 먼저 작성하고, 실패하는 테스트를 작성한 뒤, 테스트를
통과시키는 최소 구현을 하고, 마지막에 리팩토링합니다.
자세한 순서는 [CLAUDE.md](CLAUDE.md#개발-방식-sdd--tdd) 참고.

## 빌드 방법
1. `AIProject5.slnx`를 Visual Studio로 연다.
2. NuGet 패키지 관리자(Package Manager Console)에서 `gmock`이
   설치되어 있는지 확인한다. 없으면 설치한다.
3. Debug 또는 Release 구성으로 빌드한다 (Win32/x64 모두 지원).

## 테스트 방법
실행 파일에 아무 인자나 붙여서 실행하면 GoogleTest가 돈다
(Visual Studio 테스트 탐색기의 GoogleTest 어댑터도 동일하게 동작).

```
AIProject5.exe --test
```

## 실행 방법
인자 없이 실행 파일을 실행하면 콘솔 메뉴가 표시됩니다.

```
AIProject5.exe
```

```
1. Create
2. Read (전체 목록)
3. Read (id 검색)
4. Update
5. Delete
6. Exit
```

데이터는 실행 파일과 같은 위치의 `data.json` 파일에 저장됩니다.
파일이 없으면 첫 실행 시 빈 배열로 자동 생성됩니다.

## 개발 문서
- [CLAUDE.md](CLAUDE.md) — 프로젝트 목표, 아키텍처 원칙, 코딩 컨벤션
- [docs/COMMIT_CONVENTION.md](docs/COMMIT_CONVENTION.md) — 커밋 메시지 규칙
- [docs/specs/TEMPLATE.md](docs/specs/TEMPLATE.md) — 기능 스펙 작성 템플릿

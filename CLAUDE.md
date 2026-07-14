# AIProject5 — JSON 기반 CRUD 콘솔 애플리케이션

## 프로젝트 목표
익숙하지 않은 코드(JSON 라이브러리)를 직접 PoC로 다뤄보고 이해한 뒤, 그 구조를 그대로 유지한 채
JSON 파일을 데이터 저장소로 사용하는 CRUD 콘솔 애플리케이션으로 확장한다.

진행 순서는 반드시 아래 2단계를 지킨다.

1. **PoC 단계**: nlohmann/json으로 JSON 파싱 / 파일 저장만 하는 최소 예제를 작성하고 동작을 이해한다.
2. **CRUD 단계**: PoC에서 만든 코드 구조(파일 구성, 함수 분리 방식, JSON 다루는 패턴)를 그대로 유지한 채
   Create/Read/Update/Delete 기능을 얹는다. PoC 코드를 갈아엎고 새 아키텍처로 재작성하지 않는다.

## 기술 스택
- 언어: C++20 (MSVC, `stdcpp20`, PlatformToolset v145)
- 빌드: Visual Studio (`AIProject5.slnx` / `AIProject5.vcxproj`), Win32/x64 x Debug/Release
- JSON 라이브러리: [nlohmann/json](https://github.com/nlohmann/json) — NuGet(`nlohmann.json`)으로 설치
- 테스트 프레임워크: [GoogleTest](https://github.com/google/googletest) (gmock 포함) — NuGet(`gmock`)으로 설치됨
  패키지는 `packages.config`으로 관리한다 (Visual Studio NuGet 패키지 관리자 사용).
  헤더 하나만 복사해 넣는 방식은 쓰지 않는다.
- 데이터 저장: 단일 JSON 파일 (예: `data.json`), 배열 형태로 레코드 저장

## 폴더 구조 원칙
- PoC 코드와 CRUD 코드를 분리하지 않는다 — PoC 파일을 그대로 확장해 나간다.
- 제안 구조:
  ```
  AIProject5/
    AIProject5.cpp        # main, 메뉴 루프
    JsonStore.h / .cpp     # JSON 파일 read/write, PoC에서 만든 로직 그대로 재사용
    Record.h               # 데이터 모델 (struct + to_json/from_json)
    data.json               # 런타임 데이터 파일 (레포에 커밋하지 않음)
    tests/                   # GoogleTest 테스트 코드
    docs/specs/              # 기능별 스펙 문서
  ```
- 새 클래스/파일을 추가하기 전에 PoC 코드에 이미 있는 함수로 해결되는지 먼저 확인한다.

## 개발 방식 (SDD + TDD)
모든 기능은 반드시 아래 순서로 개발한다. 순서를 건너뛰지 않는다.

1. **Spec 작성**: `docs/specs/`에 기능별 스펙 md를 먼저 작성한다.
   입력, 출력, 예외/엣지 케이스를 글로 정리한다. 형식은
   [docs/specs/TEMPLATE.md](docs/specs/TEMPLATE.md) 참고.
2. **실패하는 테스트 작성**: 스펙을 기준으로 `tests/`에 GoogleTest
   테스트를 작성한다. 이 시점에는 테스트가 실패하는 것이 정상이다.
3. **최소 구현**: 테스트를 통과시키는 최소한의 코드만 작성한다.
4. **리팩토링**: 테스트가 통과하는 상태를 유지하면서 코드를 정리한다.

- 스펙 없는 기능 구현, 테스트 없는 기능 구현은 하지 않는다.
- 하나의 PR은 하나의 스펙(하나의 기능 단위)에 대응하는 것을 기본으로 한다.

## 데이터 모델
- 레코드는 최소한 다음 필드를 가진다: `id`(고유 식별자), 그 외 비즈니스 필드는 태스크에 맞게 정의.
- `id`는 프로그램이 자동 생성(예: 증가 카운터)하며 사용자 입력을 받지 않는다.

## CRUD 기능 요구사항
- **Create**: 사용자로부터 필드 값을 입력받아 새 레코드를 만들고 JSON 파일에 저장(append).
- **Read**:
  - 전체 목록 출력
  - 특정 `id` 또는 키 값으로 검색 (없으면 "결과 없음" 안내, 예외로 죽지 않아야 함)
- **Update**: `id`로 레코드를 선택 → 특정 필드만 골라 수정 → 파일에 반영.
- **Delete**: `id`로 레코드를 선택 → 삭제 전 대상 레코드를 보여주고 확인(y/n) 받은 뒤 삭제.
- 모든 쓰기 작업(Create/Update/Delete) 후에는 즉시 JSON 파일에 저장하여 프로그램 종료 시 데이터가
  유실되지 않게 한다.

## 에러 처리 원칙
- JSON 파일이 없으면 빈 배열로 새로 생성한다 (첫 실행 시 크래시 금지).
- JSON 파싱 실패, 파일 열기 실패는 예외를 잡아 사용자에게 메시지로 안내하고 프로그램을 종료하지 않는다.
- 존재하지 않는 `id`에 대한 Update/Delete/검색은 정상적인 흐름으로 처리한다(예외 아님).

## 코딩 컨벤션
- 헤더/구현 분리(.h/.cpp), 콘솔 입출력은 `main.cpp`(메뉴 루프)에만 두고 JSON 입출력 로직과 섞지 않는다.
- 주석은 WHY가 필요한 경우에만 작성한다. 코드가 스스로 설명하는 내용은 주석으로 반복하지 않는다.
- 이 프로젝트는 학습/PoC 목적이므로 과도한 추상화(인터페이스, 팩토리 패턴 등)를 넣지 않는다.
  CRUD 4개 동작을 충분히 잘 표현하는 단순한 함수/구조면 충분하다.

## 커밋 컨벤션
커밋 메시지 작성 규칙은 [docs/COMMIT_CONVENTION.md](docs/COMMIT_CONVENTION.md) 참고.

## 하지 말아야 할 것
- PoC 단계에서 만든 JSON 처리 구조를 CRUD 단계에서 뜯어고치는 것 (구조 유지가 이 과제의 핵심 학습 목표).
- 데이터베이스, ORM, 외부 설정 파일 등 이 과제 범위를 벗어난 것 추가.
- 존재하지 않는 상황에 대한 방어 코드 남발 (예: 입력 검증을 과하게 세분화).

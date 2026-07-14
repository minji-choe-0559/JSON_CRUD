# Spec: Update

## 개요
- `id`로 연락처를 찾아 `name`/`phone` 중 원하는 필드만 골라
  수정하고 파일에 반영하는 기능.

## 입력
- 파일 경로 (`std::string`), 수정할 `id` (`int`).
- 새 `name` (`std::optional<std::string>`, 값이 있으면 수정).
- 새 `phone` (`std::optional<std::string>`, 값이 있으면 수정).

## 출력
- 수정 성공 시 수정된 `Record`를 담은 `std::optional<Record>`.
- 해당 `id`가 없으면 `std::nullopt` (예외 아님).

## 엣지 케이스 / 예외 상황
- 존재하지 않는 `id`로 Update 시도 시 예외를 던지지 않고
  `std::nullopt`를 반환한다 (CLAUDE.md 에러 처리 원칙).
- `name`/`phone` 둘 다 `std::nullopt`면 아무 필드도 바꾸지 않고
  기존 레코드를 그대로 반환한다 (파일도 그대로 다시 저장됨).
- 수정 대상이 아닌 다른 레코드는 그대로 유지된다.

## 테스트 케이스 목록
- [x] 정상 케이스: name만 수정 시 phone은 그대로 유지
- [x] 정상 케이스: phone만 수정 시 name은 그대로 유지
- [x] 정상 케이스: name/phone 둘 다 수정
- [x] 정상 케이스: 수정 후 파일을 다시 읽으면 변경 내용이 반영됨
- [x] 정상 케이스: 수정 대상이 아닌 다른 레코드는 변경되지 않음
- [x] 엣지 케이스: 존재하지 않는 id로 수정 시도 시 nullopt 반환
      (예외 아님)
- [x] 엣지 케이스: name/phone 둘 다 미지정 시 기존 값 그대로 유지

# Spec: Record

## 개요
- 연락처 하나를 표현하는 데이터 모델. `id`, `name`, `phone` 필드를
  가진다.
- CRUD 전체가 다루는 최소 단위이며, `JsonValue`와 상호 변환 가능해야
  파일 저장/불러오기가 가능하다.

## 입력
- `Record { int id; std::string name; std::string phone; }` 구조체.
- `toJson(const Record&)` — Record를 object 타입 `JsonValue`로 변환.
- `fromJson(const JsonValue&)` — object 타입 `JsonValue`를 Record로
  변환.
- `readAllRecords(path)` — 파일 경로.
- `writeAllRecords(path, records)` — 파일 경로 + 저장할
  `std::vector<Record>`.

## 출력
- `toJson`: `{"id": ..., "name": ..., "phone": ...}` 형태의
  `JsonValue` (object).
- `fromJson`: 위 형태의 `JsonValue`를 읽어 만든 `Record`.
- `readAllRecords`: 파일의 모든 레코드를 담은 `std::vector<Record>`
  (Create/Read/Update/Delete가 공통으로 사용하는 저장소 접근점).
- `writeAllRecords`: 반환값 없음, 파일에 레코드 목록을 통째로 저장.

## 엣지 케이스 / 예외 상황
- `fromJson`에 object가 아닌 `JsonValue`가 들어오면 예외
  (`JsonValue::asObject()`가 이미 예외를 던지므로 별도 처리 불필요).
- `fromJson`에 `id`/`name`/`phone` 중 하나라도 없는 object가
  들어오면 예외 (`JsonValue::operator[]`가 이미 예외를 던짐).
- `id`는 CLAUDE.md 원칙에 따라 사용자 입력을 받지 않고 프로그램이
  자동 생성한다 (Record 자체는 검증하지 않고, 생성 로직은 Create
  기능 쪽 책임).

## 테스트 케이스 목록
- [ ] 정상 케이스: Record를 만들어 `toJson`으로 변환 시 각 필드가
      올바른 key/value로 들어감
- [ ] 정상 케이스: `toJson`으로 만든 JsonValue를 `fromJson`으로
      되돌리면 원래 Record와 동일 (round-trip)
- [ ] 예외 케이스: object가 아닌 JsonValue를 `fromJson`에 넣으면
      예외 발생
- [ ] 예외 케이스: 필드가 누락된 object를 `fromJson`에 넣으면
      예외 발생
- [ ] 정상 케이스: `writeAllRecords`로 저장 후 `readAllRecords`로
      다시 읽으면 동일한 목록 (round-trip)
- [ ] 엣지 케이스: 파일이 없을 때 `readAllRecords`는 빈 벡터 반환

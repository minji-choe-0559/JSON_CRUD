# Spec: JsonValue

## 개요
- JSON이 표현할 수 있는 6가지 타입(null, bool, number, string, array,
  object)을 하나의 값으로 표현하는 자료구조.
- JsonParser의 파싱 결과이자 JsonWriter의 직렬화 입력이 되는 공통 타입.

## 입력
- `JsonValue()` — 기본 생성 시 null 타입.
- `JsonValue(bool)` — bool 타입.
- `JsonValue(double)` — number 타입.
- `JsonValue(std::string)` — string 타입.
- `JsonValue(std::vector<JsonValue>)` — array 타입.
- `JsonValue(std::map<std::string, JsonValue>)` — object 타입.
  key 순서는 보장하지 않는다 (`std::map` 기준 정렬).

## 출력
- 타입 조회: `isNull()`, `isBool()`, `isNumber()`, `isString()`,
  `isArray()`, `isObject()` — 현재 값이 어떤 타입인지 bool로 반환.
- 값 접근: `asBool()`, `asNumber()`, `asString()`, `asArray()`,
  `asObject()` — 해당 타입일 때 실제 값을 반환.
- object 타입의 key 접근: `operator[](const std::string& key)` —
  해당 key의 JsonValue를 반환.
- array 타입의 index 접근: `operator[](size_t index)` —
  해당 index의 JsonValue를 반환.

## 엣지 케이스 / 예외 상황
- 현재 타입과 다른 `as*()` 호출 시 (예: string 타입에 `asNumber()`
  호출) `std::runtime_error`를 던진다.
- object가 아닌 값에 `operator[](string)` 호출 시 예외를 던진다.
- array가 아닌 값에 `operator[](size_t)` 호출 시 예외를 던진다.
- object에서 존재하지 않는 key 접근 시 예외를 던진다 (자동 생성하지
  않는다).
- array에서 범위를 벗어난 index 접근 시 예외를 던진다.

## 테스트 케이스 목록
- [ ] 정상 케이스: 각 타입(null/bool/number/string/array/object)으로
      생성 시 해당하는 `is*()`가 true 반환
- [ ] 정상 케이스: 각 타입 생성 후 `as*()`로 원래 값 그대로 조회
- [ ] 정상 케이스: object에서 존재하는 key로 값 조회
- [ ] 정상 케이스: array에서 유효한 index로 값 조회
- [ ] 엣지 케이스: 빈 array, 빈 object 생성 및 조회
- [ ] 예외 케이스: 타입이 다른 `as*()` 호출 시 예외 발생
- [ ] 예외 케이스: object에 없는 key 접근 시 예외 발생
- [ ] 예외 케이스: array에 범위 밖 index 접근 시 예외 발생

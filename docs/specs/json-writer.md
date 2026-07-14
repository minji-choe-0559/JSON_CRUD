# Spec: JsonWriter

## 개요
- `JsonValue`를 JSON 형식 문자열로 직렬화하는 기능.
- JsonParser가 문자열 -> JsonValue라면, JsonWriter는 그 반대 방향.

## 입력
- `JsonValue` (null, bool, number, string, array, object 중 하나).

## 출력
- 해당 값을 표현하는 JSON 형식 `std::string`.
  - null -> `null`
  - bool -> `true` / `false`
  - number -> 정수는 `.0` 없이, 실수는 그대로 출력
  - string -> 큰따옴표로 감싸고 특수문자 이스케이프
  - array -> `[` `]`로 감싸고 콤마로 구분
  - object -> `{` `}`로 감싸고 `"key": value` 형태, 콤마로 구분

## 엣지 케이스 / 예외 상황
- 빈 array는 `[]`, 빈 object는 `{}`로 출력.
- 문자열 안의 `"`, `\`, 개행 등은 이스케이프해서 출력
  (JsonParser가 다시 읽을 수 있어야 함).
- object의 key 순서는 `std::map` 순서(사전순)를 따른다.

## 테스트 케이스 목록
- [ ] 정상 케이스: null, true, false 직렬화
- [ ] 정상 케이스: 정수/실수/음수 직렬화
- [ ] 정상 케이스: 일반 문자열 직렬화
- [ ] 정상 케이스: 이스케이프가 필요한 문자열 직렬화
- [ ] 정상 케이스: 배열 직렬화 (빈 배열 포함)
- [ ] 정상 케이스: 객체 직렬화 (빈 객체 포함)
- [ ] 정상 케이스: 배열/객체 중첩 구조 직렬화
- [ ] round-trip 케이스: JsonWriter로 직렬화한 문자열을
      JsonParser로 다시 파싱하면 원래 값과 동일해야 함

# Task 11 – Final design
- Money as `long long` paise; never floating point.
- `enum class Zone` and `constexpr` constants; one `FarePolicy` holds every rule.
- `SmartCard` with private balance; `deduct()` and `recharge()` validate.
- Invalid hour/zone returns `std::nullopt`; invalid recharge is rejected.
- Table-driven tests; real compiler output kept with the code.
- n journeys: O(n) time, O(1) working memory when streamed.

## Revising a tariff
Change the constants in one place, update test rows. No other fare literals exist.

## Limitations
Student/senior concession percentage is not given in the brief, so it is not implemented (planned `DiscountPolicy` interface). Refunds, concurrency, security and audit logging are not modelled.

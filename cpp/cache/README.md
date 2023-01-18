TODOs:

- `KeyValuestore::get()` is not really thread-safe because it makes `accessedKey()` calls.
- Write units tests, specially for LFU and LRU policies.
- Tests for multithreading.
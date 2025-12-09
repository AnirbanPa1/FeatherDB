import subprocess

def run_script(commands):
    process = subprocess.Popen(
        ['./db'], 
        stdin=subprocess.PIPE, 
        stdout=subprocess.PIPE, 
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=0
    )
    input_data = '\n'.join(commands) + '\n'
    stdout_data, _ = process.communicate(input=input_data)
    return stdout_data.splitlines()

# Your existing test functions unchanged:
def test_inserts_and_selects():
    result = run_script([
        "insert 1 user1 person1@example.com",
        "select",
        ".exit",
    ])
    expected = [
        "FeatherDB-Test > Executed.",
        "FeatherDB-Test > (1, user1, person1@example.com)",
        "Executed.",
        "FeatherDB-Test > ",
    ]
    assert sorted(result) == sorted(expected), f"Expected {expected}, but got {result}"

def test_table_full_error():
    script = [f"insert {i} user{i} person{i}@example.com" for i in range(1, 1402)]
    script.append(".exit")
    result = run_script(script)
    assert "FeatherDB-Test > Error: Table full." in result, "Did not get 'Table full' error"

def test_max_length_strings():
    long_username = "a" * 32
    long_email = "a" * 255
    script = [
        f"insert 1 {long_username} {long_email}",
        "select",
        ".exit",
    ]
    result = run_script(script)
    expected = [
        "FeatherDB-Test > Executed.",
        f"FeatherDB-Test > (1, {long_username}, {long_email})",
        "Executed.",
        "FeatherDB-Test > ",
    ]
    assert sorted(result) == sorted(expected), "Max length string test failed"

def test_too_long_strings():
    long_username = "a" * 33
    long_email = "a" * 256
    script = [
        f"insert 1 {long_username} {long_email}",
        "select",
        ".exit",
    ]
    result = run_script(script)
    expected = [
        "FeatherDB-Test > String too long.",
        "FeatherDB-Test > Executed.",
        "FeatherDB-Test > ",
    ]
    assert sorted(result) == sorted(expected), "Too long string test failed"

def test_negative_id():
    script = [
        "insert -1 cstack foo@bar.com",
        "select",
        ".exit",
    ]
    result = run_script(script)
    expected = [
        "FeatherDB-Test > ID must be positive.",
        "FeatherDB-Test > Executed.",
        "FeatherDB-Test > ",
    ]
    assert sorted(result) == sorted(expected), "Negative ID test failed"

# New runner to track pass/fail counts and names
def run_all_tests():
    tests = [
        ("test_inserts_and_selects", test_inserts_and_selects),
        ("test_table_full_error", test_table_full_error),
        ("test_max_length_strings", test_max_length_strings),
        ("test_too_long_strings", test_too_long_strings),
        ("test_negative_id", test_negative_id),
    ]

    passed = []
    failed = []

    for name, test_func in tests:
        try:
            test_func()
            passed.append(name)
        except AssertionError as e:
            failed.append((name, str(e)))

    print(f"Tests passed: {len(passed)}")
    for p in passed:
        print(f"  - {p}")

    print(f"Tests failed: {len(failed)}")
    for f in failed:
        print(f"  - {f[0]}: {f[1]}")

if __name__ == "__main__":
    run_all_tests()

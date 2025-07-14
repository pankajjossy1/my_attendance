-- Table: teachers
CREATE TABLE IF NOT EXISTS teachers (
    teacher_id TEXT PRIMARY KEY,
    firstname TEXT NOT NULL,
    password_hash TEXT NOT NULL,
    department TEXT NOT NULL
);

-- Table: students
CREATE TABLE IF NOT EXISTS students (
    student_id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    semester INT NOT NULL,
    department TEXT NOT NULL
);

-- Table: subjects
CREATE TABLE IF NOT EXISTS subjects (
    subject_code TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    department TEXT NOT NULL,
    type TEXT CHECK (type IN ('Departmental', 'Interdisciplinary'))
);

-- Table: student_subjects (many-to-many)
CREATE TABLE IF NOT EXISTS student_subjects (
    student_id TEXT REFERENCES students(student_id) ON DELETE CASCADE,
    subject_code TEXT REFERENCES subjects(subject_code) ON DELETE CASCADE,
    PRIMARY KEY (student_id, subject_code)
);

-- Table: attendance
CREATE TABLE IF NOT EXISTS attendance (
    id SERIAL PRIMARY KEY,
    student_id TEXT REFERENCES students(student_id) ON DELETE CASCADE,
    subject_code TEXT REFERENCES subjects(subject_code) ON DELETE CASCADE,
    date DATE NOT NULL,
    timestamp TIMESTAMP NOT NULL,
    session_id TEXT,
    teacher_id TEXT REFERENCES teachers(teacher_id),
    status TEXT CHECK (status IN ('Present', 'Absent')) NOT NULL
);

-- Table: sessions
CREATE TABLE IF NOT EXISTS sessions (
    session_id TEXT PRIMARY KEY,
    teacher_id TEXT REFERENCES teachers(teacher_id),
    subject_code TEXT REFERENCES subjects(subject_code),
    semester INT NOT NULL,
    timestamp TIMESTAMP NOT NULL,
    is_used BOOLEAN DEFAULT FALSE,
    expires_at TIMESTAMP NOT NULL
);

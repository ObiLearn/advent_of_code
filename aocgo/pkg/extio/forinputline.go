package extio

import (
	"io"
)

func ForInputLine(cb func(string)) error {
	reader, err := PipeReader()
	if err != nil {
		return err
	}

	for {
		line, err := Readln(reader)

		if err != nil {
			if err == io.EOF {
				//break loop on EOF
				break
			} else {
				return err
			}
		}

		cb(line)
	}

	return nil
}

func InputLines() (<-chan string, <-chan error) {
	out := make(chan string)
	errs := make(chan error)

	reader, err := PipeReader()
	if err != nil {
		errs <- err
		close(out)
		close(errs)
		return out, errs
	}

	go func() {
		defer close(out)
		defer close(errs)

		for {
			line, err := Readln(reader)

			if err != nil {
				if err != io.EOF {
					errs <- err
				}
				break
			}
			out <- line
		}
	}()

	return out, errs
}

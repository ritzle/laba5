use std::collections::HashMap;
use std::io;
use rand::Rng;//rand

type Queue = HashMap<usize, Vec<(String, i32)>>;

fn data_input(queue: &mut Queue) {
    loop {
        let mut request = String::new();
        println!(": ");
        io::stdin().read_line(&mut request).unwrap();
        let request = request.trim();

        if request == "ENQUEUE" {
            let mut time = String::new();
            io::stdin().read_line(&mut time).unwrap();
            let time: i32 = time.trim().parse().unwrap();

            let ticket = ticket_generation(queue);
            let num_windows = finding_min_time(queue);
            queue.get_mut(&num_windows).unwrap().push((ticket.clone(), time));
            println!("{}", ticket);
        } else if request == "DISTRIBUTE" {
            print_queue(queue);
            break;
        } else {
            println!("Error. Re-enter");
        }
    }
}

fn finding_min_time(queue: &Queue) -> usize {
    let mut num_windows = 0;
    let mut min_time = 0;

    for (_, tickets) in queue.get(&0).unwrap() {
        min_time += tickets;
    }

    for (window, tickets) in queue {
        let mut time = 0;
        for ticket in tickets {
            time += ticket.1;
        }
        if time < min_time {
            num_windows = *window;
            min_time = time;
        }
    }

    num_windows
}

fn ticket_generation(queue: &Queue) -> String {
    let mut ticket = String::new();
    let mut unique_ticket = false;

    while !unique_ticket {
        let rand_ticket = rand::thread_rng().gen_range(0..1000);
        ticket = format!("T{}", rand_ticket);

        unique_ticket = true;
        for (_window, tickets) in queue {
            for (t, _) in tickets {
                if t == &ticket {
                    unique_ticket = false;
                    break;
                }
            }
            if !unique_ticket {
                break;
            }
        }
    }

    ticket
}

fn print_queue(queue: &Queue) {
    let mut window = 0;
    for (window_num, tickets) in queue {
        let all_time = all_time_windows(queue, window);
        window += 1;
        println!("Windows {} {} minutes: ", window_num + 1, all_time);
        for (ticket, _) in tickets {
            print!("{} ", ticket);
        }
        println!();
    }
}

fn all_time_windows(queue: &Queue, windows: usize) -> i32 {
    let mut time = 0;
    for (_, t) in queue.get(&windows).unwrap() {
        time += t;
    }
    time
}

fn main() {
    let mut queue: Queue = HashMap::new();

    println!("enter number of windows: ");
    let mut num_windows = String::new();
    io::stdin().read_line(&mut num_windows).unwrap();
    let num_windows: usize = num_windows.trim().parse().unwrap();

    for i in 0..num_windows {
        queue.insert(i, Vec::new());
    }

    data_input(&mut queue);
}

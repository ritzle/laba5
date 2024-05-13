use std::collections::HashMap;
use std::io::{self, Write};

const MAX_CELL_SIZE: usize = 10;
const TOTAL_NUMBER_RACK: usize = 4;
const TOTAL_NUMBER_VERTICAL_SELECTION: usize = 18;
const TOTAL_SHELF_NUMBER: usize = 5;
const TOTAL_PRODUCT_STOCK: usize = 7200;

type Stock = HashMap<char, Vec<Vec<Vec<HashMap<String, i32>>>>>;

fn add_product(
    name_product: &str,
    count_product: i32,
    cell_address: &str,
    stock: &mut Stock,
) -> bool {
    if count_product > 10 {
        println!("cell can only store 10 units");
        return false;
    }

    let storage_area = cell_address.chars().next().unwrap();
    let number_rack = cell_address[1..3].parse::<usize>().unwrap() - 1;
    let number_vertical_section = cell_address[3..5].parse::<usize>().unwrap() - 1;
    let shelf_number = cell_address[5..].parse::<usize>().unwrap() - 1;

    if (storage_area != 'A' && storage_area != 'B')
        || number_rack >= TOTAL_NUMBER_RACK
        || number_vertical_section >= TOTAL_NUMBER_VERTICAL_SELECTION
        || shelf_number >= TOTAL_SHELF_NUMBER
    {
        println!("Invalid cell address");
        return false;
    }

    let stock_entry = stock
        .entry(storage_area)
        .or_insert_with(|| {
            vec![
                vec![
                    HashMap::new();
                    TOTAL_NUMBER_VERTICAL_SELECTION
                ];
                TOTAL_NUMBER_RACK
            ]
        });

    let number_product_units_shelf = quantity_shelf_occupancy(stock, storage_area, number_rack, number_vertical_section, shelf_number);

    if number_product_units_shelf + count_product <= MAX_CELL_SIZE {
        stock_entry[number_rack][number_vertical_section][shelf_number]
            .entry(name_product.to_string())
            .and_modify(|count| *count += count_product)
            .or_insert(count_product);
        true
    } else {
        println!(
            "now on the shelf {} \ntotal shelf can store {} units of product",
            number_product_units_shelf, MAX_CELL_SIZE
        );
        false
    }
}

fn quantity_shelf_occupancy(
    stock: &Stock,
    storage_area: char,
    number_rack: usize,
    number_vertical_section: usize,
    shelf_number: usize,
) -> i32 {
    let mut number_product_units_shelf = 0;

    if let Some(inner_map) = stock.get(&storage_area).and_then(|v| v.get(number_rack)).and_then(|v| v.get(number_vertical_section)).and_then(|v| v.get(shelf_number)) {
        for (_, count) in inner_map {
            number_product_units_shelf += count;
        }
    }

    number_product_units_shelf
}

fn remove_product(
    name_product: &str,
    count_product: i32,
    cell_address: &str,
    stock: &mut Stock,
) -> bool {
    if count_product > 10 {
        println!("No more than 10 can be deleted at a time");
        return false;
    }

    let storage_area = cell_address.chars().next().unwrap();
    let number_rack = cell_address[1..3].parse::<usize>().unwrap() - 1;
    let number_vertical_section = cell_address[3..5].parse::<usize>().unwrap() - 1;
    let shelf_number = cell_address[5..].parse::<usize>().unwrap() - 1;

    if (storage_area != 'A' && storage_area != 'B')
        || number_rack >= TOTAL_NUMBER_RACK
        || number_vertical_section >= TOTAL_NUMBER_VERTICAL_SELECTION
        || shelf_number >= TOTAL_SHELF_NUMBER
    {
        println!("Invalid cell address");
        return false;
    }

    if let Some(inner_map) = stock.get_mut(&storage_area).and_then(|v| v.get_mut(number_rack)).and_then(|v| v.get_mut(number_vertical_section)).and_then(|v| v.get_mut(shelf_number)) {
        if let Some(count) = inner_map.get_mut(name_product) {
            if *count - count_product < 0 {
                println!("{} is less of this product than you want to remove", name_product);
                return false;
            } else {
                *count -= count_product;
                if *count == 0 {
                    inner_map.remove(name_product);
                }
                true
            }
        } else {
            println!("product not found");
            false
        }
    } else {
        println!("Stock empty");
        false
    }
}

fn info(stock: &Stock) {
    if stock.is_empty() {
        println!("Stock empty");
        return;
    }

    let mut counter_product = 0.0;
    let mut counter_product_sector_a = 0.0;
    let mut counter_product_sector_b = 0.0;

    for (storage_area, racks) in stock {
        for rack in racks {
            for vertical_section in rack {
                for shelf in vertical_section {
                    for (name_product, count) in shelf {
                        counter_product += *count as f32;
                        if *storage_area == 'A' {
                            counter_product_sector_a += *count as f32;
                        } else if *storage_area == 'B' {
                            counter_product_sector_b += *count as f32;
                        }

                        if *count != 0 {
                            println!(
                                "{}-{}-{}-{}-{} = {}",
                                storage_area, rack.index() + 1, vertical_section.index() + 1, shelf.index() + 1, name_product, count
                            );
                        }
                    }
                }
            }
        }

        if *storage_area == 'A' {
            println!(
                "{:.2}% - sector A",
                (counter_product_sector_a * 100.0) / (TOTAL_PRODUCT_STOCK as f32 / 2.0)
            );
        } else if *storage_area == 'B' {
            println!(
                "{:.2}% - sector B",
                (counter_product_sector_b * 100.0) / (TOTAL_PRODUCT_STOCK as f32 / 2.0)
            );
        }
        println!();
    }

    println!();
    println!("{:.2}% - fullness", (counter_product * 100.0) / TOTAL_PRODUCT_STOCK as f32);
}

fn add(stock: &mut Stock) {
    let mut name_product = String::new();
    let mut count_product: i32 = 0;
    let mut cell_address = String::new();

    print!("nameProduct: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut name_product).unwrap();
    name_product = name_product.trim().to_string();

    print!("countProduct: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut count_product).unwrap();
    count

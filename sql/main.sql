create table items (
  id integer primary key autoincrement,
  name text not null,
  price real default 0,
  unitAmount integer not null default 1,
  unit text not null default 'piece',
  image blob
);

create table users (
  id integer primary key autoincrement,
  name text not null,
  avatar blob,
  dob text
);

create table accounts (
  id integer primary key autoincrement,
  name text not null,
  balance real default 0,
  userId integer references users(id),
  unique(userId, accountName)
);

create table transactions (
    accountId integer references accounts(id),
    ammount real not null,
    date text,
    note text
);

create table carts (
  id integer primary key autoincrement,
  userId integer references users(id)
);

create table cartItems (
  id integer primary key autoincrement,
  itemId integer not null references items(id),
  cartId integer not null references carts(id),
  qty integer not null
);

create table app (
  property text not null primary key,
  value text
);

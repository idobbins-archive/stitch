
vim.api.nvim_set_keymap("n", "<F4>", "<cmd>:w | !cargo fmt && cargo test<CR>", {})
vim.api.nvim_set_keymap("n", "<F5>", "<cmd>:w | !cargo fmt && cargo run<CR>", {})


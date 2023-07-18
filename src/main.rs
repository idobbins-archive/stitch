use clap::Parser;

/// Command line tool to stitch videos together
#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Left video feed
    #[arg(short)]
    left: String,

    /// Right video feed
    #[arg(short)]
    right: String,

    /// Output file path
    #[arg(short)]
    out: String,
}

fn main() {
    let args = Args::parse();
}

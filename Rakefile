# frozen_string_literal: true

require "bundler/gem_tasks"

require "rake/clean"
CLEAN.include("**/*.o", "**/*.so", "**/*.bundle", "pkg", "tmp")

require "rake/extensiontask"
%w[precomputed ref10].each do |provider|
  next if provider == "precomputed" && RUBY_PLATFORM !~ /x86_64|x64/

  Rake::ExtensionTask.new("x25519_#{provider}") do |ext|
    ext.ext_dir = "ext/x25519_#{provider}"
  end
end

require "rspec/core/rake_task"
RSpec::Core::RakeTask.new

require "rubocop/rake_task"
RuboCop::RakeTask.new

task default: %w[compile spec rubocop]
